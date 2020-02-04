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

using namespace std;
using namespace llvm;

namespace {
  struct ShackletonPass : public ModulePass {
      static char ID;
      ShackletonPass() : ModulePass(ID) {}
      
      virtual bool runOnModule(Module &M); //when there is a Module
      virtual bool runOnFunction(Function &F, Module &M); //called by runOnModule
      virtual bool runOnBasicBlock(BasicBlock &BB, Module &M); // called by runOnFunction
      
      bool initialize(Module &M); //create global variable
      bool finialize(Module &M); //print global variable
      void createInstr(BasicBlock &bb, Constant *counter_ptr, int num);
      
      vector<string> atomicCounter = {"instructionCounter", "basicBlockCounter", "mulCounter", "memOpCounter", "branchCounter"}; //keep global variable names for profiling. e.g. instr counter
  };
}

bool ShackletonPass::runOnModule(Module &M)
{
    bool modified = initialize(M);
    
    for (auto it = M.begin(); it != M.end(); it++) {
        modified |= runOnFunction(*it, M);
    }
    modified |= finialize(M);
    //M.dump();
    
    return modified;
}

bool ShackletonPass::runOnFunction(Function &F, Module &M)
{
    bool modified = false;
    //errs() << F.getName() << "\n";
  
    for (auto it = F.begin(); it != F.end(); it++) {
        if (it==F.begin()){
            Type *I64Ty = Type::getInt64Ty(M.getContext());
            IRBuilder<> Builder(F.getContext());
            Twine s = F.getName()+".glob";
            Value *atomicCounter = M.getOrInsertGlobal(s.str(), I64Ty);
            Value *One = ConstantInt::get(Type::getInt64Ty(F.getContext()), 1);
            
            new AtomicRMWInst(AtomicRMWInst::Add,
                              atomicCounter,
                              ConstantInt::get(Type::getInt64Ty(F.getContext()), 1),
                              AtomicOrdering::SequentiallyConsistent,
                              SyncScope::System, it->getFirstNonPHI ());
                              
        }
        
        modified |= runOnBasicBlock(*it, M);
        
    }

    //Value *result = Builder.CreateAdd(atomicCounter,One,"func_add");
    
    return modified;
}

void ShackletonPass::createInstr(BasicBlock &bb, Constant *counter_ptr, int num){
    if(num){ // create atomic addition instruction
        new AtomicRMWInst(AtomicRMWInst::Add,
                      counter_ptr, // pointer to global variable
                      ConstantInt::get(Type::getInt64Ty(bb.getContext()), num), //create integer with value num
                      AtomicOrdering::SequentiallyConsistent, //operations may not be reordered
                      SyncScope::System, // synchronize to all threads
                      bb.getTerminator()); //insert right before block terminator
    }
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
    int mul_instr = 0;
    int br_instr = 0;
    int mem_instr = 0;
    
    instr += bb.size();
    for (auto it = bb.begin(); it != bb.end(); it++) {
        //errs() << it->getOpcodeName() << "\n";
        switch (it->getOpcode()) {
            case Instruction::Mul: // multiplication
                mul_instr++;
                continue;
            case Instruction::Br: // branch
                br_instr++;
                continue;
            case Instruction::Store: // store
            case Instruction::Load: // load
                mem_instr++;
                continue;
            default:
                break;
        }
    }
    
    // create atomic addition instruction
    createInstr(bb, instrCounter[0], instr);
    createInstr(bb, instrCounter[1], basic_block);
    createInstr(bb, instrCounter[2], mul_instr);
    createInstr(bb, instrCounter[3], br_instr);
    createInstr(bb, instrCounter[4], mem_instr);
    
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
