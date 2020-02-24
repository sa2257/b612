// Initially taken from llvm_profiling/skeleton/Skeleton.cpp at https://github.com/neiladit/llvm_profiling.git and later modified by Sachille Atapattu

#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include <string.h>
#include <vector>

#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace llvm;

static cl::opt<string> InputModule("function", cl::desc("Specify function to run pass"), cl::value_desc("module"));
static cl::opt<bool> SwitchOn("select", cl::desc("Select to run pass"));

namespace {
  struct ShackletonPass : public ModulePass {
      static char ID;
      ShackletonPass() : ModulePass(ID) {}
      
      virtual bool runOnModule(Module &M); //when there is a Module
      virtual bool runOnFunction(Function &F, Module &M); //called by runOnModule
      virtual bool runOnBasicBlock(BasicBlock &BB, Module &M); // called by runOnFunction
      
      bool initialize(Module &M); //create global variable
      bool finialize(Module &M); //print global variable
      void createInstr(BasicBlock &bb, Constant *counter_ptr, int num, bool loc);
      
      vector<string> atomicCounter = {  "instructionCounter", "basicBlockCounter", 
                                        "addCounter", "subCounter", "mulCounter", "divCounter", "remCounter",
                                        "andCounter", "orCounter", "xorCounter",
                                        "branchCounter", "switchCounter",
                                        "storeCounter", "loadCounter",
                                        "otherCount",
                                        "faddCounter", "fsubCounter", "fmulCounter", "fdivCounter", "fremCounter"
                                     }; //keep global variable names for profiling. e.g. instr counter
  };
}

bool ShackletonPass::runOnModule(Module &M)
{
    bool modified = initialize(M);
    
    errs() << "Pass run status: " << SwitchOn << "\n";
    errs() << "Pass running on: " << InputModule << "\n";
    for (auto func = M.begin(); func != M.end(); func++) {
        modified |= runOnFunction(*func, M);
    }
    modified |= finialize(M);
    //M.dump();
    
    return modified;
}

void ShackletonPass::createInstr(BasicBlock &bb, Constant *counter_ptr, int num, bool loc){
    Instruction *before  = loc ? bb.getTerminator() : bb.getFirstNonPHI();
    if(num){ // create atomic addition instruction
        new AtomicRMWInst(AtomicRMWInst::Add,
                      counter_ptr, // pointer to global variable
                      ConstantInt::get(Type::getInt64Ty(bb.getContext()), num), //create integer with value num
                      AtomicOrdering::SequentiallyConsistent, //operations may not be reordered
                      SyncScope::System, // synchronize to all threads
                      before); //insert right before block terminator
    }
}

bool ShackletonPass::runOnFunction(Function &F, Module &M)
{
    bool modified = false;
    //errs() << F.getName() << "\n";
    string funcName = F.getName();

    for (auto bb = F.begin(); bb != F.end(); bb++) {
        if (SwitchOn || funcName == InputModule) {
            modified |= runOnBasicBlock(*bb, M);
        }
        
        //if (bb==F.begin()){
        //    Type *I64Ty = Type::getInt64Ty(M.getContext());
        //    IRBuilder<> Builder(F.getContext());
        //    Twine s = F.getName()+".glob";
        //    Constant *atomicCounter = M.getOrInsertGlobal(s.str(), I64Ty);
        //    Value *One = ConstantInt::get(Type::getInt64Ty(F.getContext()), 1);
        //    
        //    createInstr(*bb, atomicCounter, 1, false);
        //    modified |= true;                  
        //}
    }

    return modified;
}

bool ShackletonPass::runOnBasicBlock(BasicBlock &bb, Module &M)
{
    // Get the global variable for atomic counter
    Type *I64Ty = Type::getInt64Ty(M.getContext());
    Constant *instrCounter[atomicCounter.size()];
    for (int i = 0; i < atomicCounter.size(); i++){
        instrCounter[i] = M.getOrInsertGlobal(atomicCounter[i], I64Ty);
        char message[1024];
        sprintf(message, "Could not declare or find one global var");
        //string message = string("Could not declare or find ") + atomicCounter[i] + " global";
        assert(instrCounter[i] && message);
    }
    
    // get instruction number and basic block number.
    int instr = 0;
    int basic_block = 1;
    int add_instr = 0;
    int sub_instr = 0;
    int mul_instr = 0;
    int div_instr = 0;
    int rem_instr = 0;
    int fadd_instr = 0;
    int fsub_instr = 0;
    int fmul_instr = 0;
    int fdiv_instr = 0;
    int frem_instr = 0;
    int and_instr = 0;
    int or_instr = 0;
    int xor_instr = 0;
    int br_instr = 0;
    int sw_instr = 0;
    int str_instr = 0;
    int ld_instr = 0;
    int other = 0;
    
    instr += bb.size(); // this includes atomicrmws introduced by this pass
    for (auto it = bb.begin(); it != bb.end(); it++) {
        switch (it->getOpcode()) {
            case Instruction::Add: // addition
                add_instr++;
                continue;
            case Instruction::Sub: // subtraction
                sub_instr++;
                continue;
            case Instruction::Mul: // multiplication
                mul_instr++;
                continue;
            case Instruction::UDiv: // division unsigned
            case Instruction::SDiv: // division signed
                div_instr++;
                continue;
            case Instruction::URem: // remainder unsigned
            case Instruction::SRem: // remainder signed
                rem_instr++;
                continue;
            case Instruction::FAdd: // fp addition
                fadd_instr++;
                continue;
            case Instruction::FSub: // fp subtraction
                fsub_instr++;
                continue;
            case Instruction::FMul: // fp multiplication
                fmul_instr++;
                continue;
            case Instruction::FDiv: // fp division
                fdiv_instr++;
                continue;
            case Instruction::FRem: // fp remainder
                frem_instr++;
                continue;
            case Instruction::And: // and
                and_instr++;
                continue;
            case Instruction::Or: // or
                or_instr++;
                continue;
            case Instruction::Xor: // xor
                xor_instr++;
                continue;
            case Instruction::Br: // branch
                br_instr++;
                continue;
            case Instruction::Switch: // switch
                sw_instr++;
                continue;
            case Instruction::Store: // store
                str_instr++;
                continue;
            case Instruction::Load: // load
                ld_instr++;
                continue;
            case Instruction::Alloca: // allocate stack memory
            case Instruction::Call: // function call
            case Instruction::Ret: // return
                continue;
            default:
            //    errs() << it->getOpcodeName() << "\n";
                other++;
                break;
        }
    }
    
    // create atomic addition instruction
    createInstr(bb, instrCounter[0] , instr      , true);
    createInstr(bb, instrCounter[1] , basic_block, true);
    createInstr(bb, instrCounter[2] , add_instr  , true);
    createInstr(bb, instrCounter[3] , sub_instr  , true);
    createInstr(bb, instrCounter[4] , mul_instr  , true);
    createInstr(bb, instrCounter[5] , div_instr  , true);
    createInstr(bb, instrCounter[6] , rem_instr  , true);
    createInstr(bb, instrCounter[7] , and_instr  , true);
    createInstr(bb, instrCounter[8] , or_instr   , true);
    createInstr(bb, instrCounter[9] , xor_instr  , true);
    createInstr(bb, instrCounter[10], br_instr   , true);
    createInstr(bb, instrCounter[11], sw_instr   , true);
    createInstr(bb, instrCounter[12], str_instr  , true);
    createInstr(bb, instrCounter[13], ld_instr   , true);
    createInstr(bb, instrCounter[14], other      , true);
    createInstr(bb, instrCounter[15], fadd_instr , true);
    createInstr(bb, instrCounter[16], fsub_instr , true);
    createInstr(bb, instrCounter[17], fmul_instr , true);
    createInstr(bb, instrCounter[18], fdiv_instr , true);
    createInstr(bb, instrCounter[19], frem_instr , true);
    
    return true;
}

bool ShackletonPass::initialize(Module &M)
{
    IRBuilder<> Builder(M.getContext());
    Function *mainFunc = M.getFunction("main");
        
    // not the main module
    if (!mainFunc)
        return false;
    
    Type *I64Ty = Type::getInt64Ty(M.getContext());
    // Create atomic counter global variable;
    
    for (int i = 0; i < atomicCounter.size(); i++){
        new GlobalVariable(M, I64Ty, false, GlobalValue::CommonLinkage, ConstantInt::get(I64Ty, 0), atomicCounter[i]);
    }
    
    auto &functionList = M.getFunctionList();
    for (auto &function : functionList) {
        Value *atomic_counter = new GlobalVariable(M, I64Ty, false, GlobalValue::CommonLinkage, ConstantInt::get(I64Ty, 0), function.getName()+".glob");
    }
    
    return true;
}

bool ShackletonPass::finialize(Module &M){
    
    IRBuilder<> Builder(M.getContext());
    Function *mainFunc = M.getFunction("main");
    
    // not the main module
    if (!mainFunc)
        return false;
    // Build printf function handle
    std::vector<Type *> FTyArgs;
    FTyArgs.push_back(Type::getInt8PtrTy(M.getContext())); // specify the first argument, i8* is the return type of CreateGlobalStringPtr
    FunctionType *FTy = FunctionType::get(Type::getInt32Ty(M.getContext()), FTyArgs, true); // create function type with return type, argument types and if const argument
    FunctionCallee printF = M.getOrInsertFunction("printf", FTy); // create function if not extern or defined
    
    //assert(printF != NULL);
    
    for (auto bb = mainFunc->begin(); bb != mainFunc->end(); bb++) {
        for(auto it = bb->begin(); it != bb->end(); it++) {
            // insert at the end of main function
            if ((std::string)it->getOpcodeName() == "ret") {
                 // insert printf at the end of main function, before return function
                Builder.SetInsertPoint(&*bb, it);
                for(int i = 0; i < atomicCounter.size(); i++){
                    // Build Arguments
                    Value *format_long;
                    if (i == 0){
                    format_long = Builder.CreateGlobalStringPtr("\n\n"+atomicCounter[i]+": %ld\n", "formatLong"); // create global string variable formatLong, add suffix(.1/.2/...) if already exists
                    }else{
                        format_long = Builder.CreateGlobalStringPtr(atomicCounter[i]+": %ld\n", "formatLong");
                    }
                    std::vector<Value *> argVec;
                    argVec.push_back(format_long);
                    
                    Value *atomic_counter = M.getGlobalVariable(atomicCounter[i]); // get pointer pointing to the global variable name
                    Value* finalVal = new LoadInst(atomic_counter, atomic_counter->getName()+".val", &*it); // atomic_counter only points to a string, but we want to print the number the string stores
                    argVec.push_back(finalVal);
                    CallInst::Create(printF, argVec, "printf", &*it); //create printf function with the return value name called printf (with suffix if already exists)
                    
                }
                
                Value *format_empty;
                format_empty = Builder.CreateGlobalStringPtr("\n\n", "formatEmpty"); // create empty string
                std::vector<Value *> argVec;
                argVec.push_back(format_empty);
                CallInst::Create(printF, argVec, "printf", &*it); //create printf function for a new line
                
                Value *format_long;
                
                auto &functionList = M.getFunctionList(); // gets the list of functions
                Type *I64Ty = Type::getInt64Ty(M.getContext());
                for (auto &function : functionList) { //iterates over the list
                    
                    format_long = Builder.CreateGlobalStringPtr(function.getName().str()+": %ld\n", "formatLong"); // create a global variable, name it based on the function name
                    std::vector<Value *> argVec;
                    argVec.push_back(format_long);
                    Twine s = function.getName()+".glob";
                    Value *atomicCounter = M.getGlobalVariable(s.str(),I64Ty);

                    Value* finalVal = new LoadInst(atomicCounter, function.getName()+".val", &*it);
                    
                    argVec.push_back(finalVal);
                    CallInst::Create(printF, argVec, "printf", &*it);
                }

            }
        }
    }
    return true;
    
}

char ShackletonPass::ID = 0;

// Register the pass so `opt -shackleton` runs it.
static RegisterPass<ShackletonPass> X("shackleton", "a profiling pass");
