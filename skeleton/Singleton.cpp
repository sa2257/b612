// Initially taken from llvm-pass-skeleton/skeleton/Skeleton.cpp at https://github.com/sampsyo/llvm-pass-skeleton.git and later modified by Sachille Atapattu

/* Singleton: Combines Stilton which allocates and Shelton with checks dependencies */

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
  struct StiltonPass : public ModulePass {
      static char ID;
      StiltonPass() : ModulePass(ID) {}
      
      virtual bool runOnModule(Module &M); //when there is a Module
      virtual bool runOnFunction(Function &F, Module &M); //called by runOnModule
      virtual bool runOnBasicBlock(BasicBlock &BB, Module &M); // called by runOnFunction
      
      bool initialize(Module &M); //create global variable
      bool finialize(Module &M); //print global variable
      void createInstr(BasicBlock &bb, Constant *counter_ptr, int num, bool loc);

      //int d_ratio = 1; int m_ratio = 2; int a_ratio = 3; int l_ratio = 3;
      //int f_ratio = 0; int i_ratio = 1;
      //int dmal_total = d_ratio + m_ratio + a_ratio + l_ratio;
      //int fi_total = f_ratio + i_ratio;
      //int pe_len = 3;
      int d_ratio = 1; int m_ratio = 1; int a_ratio = 1; int l_ratio = 1;
      int f_ratio = 1; int i_ratio = 3;
      int dmal_total = d_ratio + m_ratio + a_ratio + l_ratio;
      int fi_total = f_ratio + i_ratio;
      int pe_len = 4;
  };
}

bool StiltonPass::runOnModule(Module &M)
{
    bool modified = initialize(M);
    
    errs() << "Pass run status: " << SwitchOn << "\n";
    errs() << "Pass running on: " << InputModule << "\n";
    
    int idiv_pes = pe_len * pe_len * d_ratio * i_ratio / dmal_total / fi_total;
    int imul_pes = pe_len * pe_len * m_ratio * i_ratio / dmal_total / fi_total;
    int iari_pes = pe_len * pe_len * a_ratio * i_ratio / dmal_total / fi_total;
    int ilog_pes = pe_len * pe_len * l_ratio * i_ratio / dmal_total / fi_total;
    int fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total;
    int fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total;
    int fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total;
    int flog_pes = pe_len * pe_len * l_ratio * f_ratio / dmal_total / fi_total;
    int mem_units = (pe_len + 1) * (pe_len + 1);
    errs() << "Available resources: " << 
        idiv_pes << "," << imul_pes << "," << iari_pes << "," <<
        fdiv_pes << "," << fmul_pes << "," << fari_pes << "," <<
        ilog_pes << "," << flog_pes << "," << mem_units << "\n" ;
    
    for (auto func = M.begin(); func != M.end(); func++) {
        modified |= runOnFunction(*func, M);
    }
    modified |= finialize(M);
    
    return modified;
}

void StiltonPass::createInstr(BasicBlock &bb, Constant *counter_ptr, int num, bool loc){
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

bool StiltonPass::runOnFunction(Function &F, Module &M)
{
    bool modified = false;
    string funcName = F.getName();

    for (auto bb = F.begin(); bb != F.end(); bb++) {
        if (SwitchOn || funcName == InputModule) {
            modified |= runOnBasicBlock(*bb, M);
        }
    }

    return modified;
}

bool StiltonPass::runOnBasicBlock(BasicBlock &bb, Module &M)
{
    // available pe resources.
    int idiv_pes = pe_len * pe_len * d_ratio * i_ratio / dmal_total / fi_total;
    int imul_pes = pe_len * pe_len * m_ratio * i_ratio / dmal_total / fi_total;
    int iari_pes = pe_len * pe_len * a_ratio * i_ratio / dmal_total / fi_total;
    int ilog_pes = pe_len * pe_len * l_ratio * i_ratio / dmal_total / fi_total;
    int fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total;
    int fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total;
    int fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total;
    int flog_pes = pe_len * pe_len * l_ratio * f_ratio / dmal_total / fi_total;
    int mem_units = (pe_len + 1) * (pe_len + 1);
    bool fail = false;
    
    errs() << "Basic block of size " << bb.size() << "\n";
    for (auto it = bb.begin(); it != bb.end(); it++) {
        switch (it->getOpcode()) {
            case Instruction::Add: // addition
                iari_pes--;
                continue;
            case Instruction::Sub: // subtraction
                iari_pes--;
                continue;
            case Instruction::Mul: // multiplication
                imul_pes--;
                continue;
            case Instruction::UDiv: // division unsigned
            case Instruction::SDiv: // division signed
                idiv_pes--;
                continue;
            case Instruction::URem: // remainder unsigned
            case Instruction::SRem: // remainder signed
                idiv_pes--;
                continue;
            case Instruction::FAdd: // fp addition
                fari_pes--;
                continue;
            case Instruction::FSub: // fp subtraction
                fari_pes--;
                continue;
            case Instruction::FMul: // fp multiplication
                fmul_pes--;
                continue;
            case Instruction::FDiv: // fp division
                fdiv_pes--;
                continue;
            case Instruction::FRem: // fp remainder
                fdiv_pes--;
                continue;
            case Instruction::And: // and
                ilog_pes--;
                continue;
            case Instruction::Or: // or
                ilog_pes--;
                continue;
            case Instruction::Xor: // xor
                ilog_pes--;
                continue;
            case Instruction::Trunc: // truncate
                ilog_pes--;
                continue;
            case Instruction::ZExt: // zero extend
                ilog_pes--;
                continue;
            case Instruction::SExt: // sign extend
                ilog_pes--;
                continue;
            case Instruction::Shl: // shift left
                ilog_pes--;
                continue;
            case Instruction::LShr: // logic shift right
                ilog_pes--;
                continue;
            case Instruction::AShr: // arith shift right
                ilog_pes--;
                continue;
            case Instruction::ICmp: // integer compare
                ilog_pes--;
                continue;
            case Instruction::PHI: // PHI node
                ilog_pes--;
                continue;
            case Instruction::FCmp: // fp compare
                flog_pes--;
                continue;
            case Instruction::FPTrunc: // fp truncate
                flog_pes--;
                continue;
            case Instruction::FPExt: // fp extend
                flog_pes--;
                continue;
            case Instruction::FPToUI: // fp to unsigned int
                flog_pes--;
                continue;
            case Instruction::FPToSI: // fp to signed int
                flog_pes--;
                continue;
            case Instruction::UIToFP: // unsigned int to fp
                flog_pes--;
                continue;
            case Instruction::SIToFP: // signed int to fp
                flog_pes--;
                continue;
            case Instruction::Br: // branch
                continue;
            case Instruction::Switch: // switch
                continue;
            case Instruction::Store: // store
                mem_units--;
                continue;
            case Instruction::Load: // load
                mem_units--;
                continue;
            case Instruction::Call: // function call
                mem_units--;
                continue;
            case Instruction::Alloca: // Ignore allocate stack
                continue;
            case Instruction::GetElementPtr: // Ignore get address
                continue;
            case Instruction::BitCast: // Ignore convert type without bit change
                continue;
            case Instruction::Ret: // Ignore return
                continue;
            default:
                errs() << "Can't map bb, instruction " << it->getOpcodeName() << " not supported!" << "\n";
                fail = true;
                break;
        }
    }

    if(idiv_pes < 0) {
        errs() << "Can't map bb, out of int-division resources!" << "\n";
    } else if(imul_pes < 0) {
        errs() << "Can't map bb, out of int-multiply resources!" << "\n";
    } else if(iari_pes < 0) {
        errs() << "Can't map bb, out of int-arithmetic resources!" << "\n";
    } else if(fdiv_pes < 0) {
        errs() << "Can't map bb, out of fp-division resources!" << "\n";
    } else if(fmul_pes < 0) {
        errs() << "Can't map bb, out of fp-multiply resources!" << "\n";
    } else if(fari_pes < 0) {
        errs() << "Can't map bb, out of fp-arithmetic resources!" << "\n";
    } else if(ilog_pes < 0) {
        errs() << "Can't map bb, out of logic resources!" << "\n";
    } else if(flog_pes < 0) {
        errs() << "Can't map bb, out of fp-compare resources!" << "\n";
    } else if(mem_units < 0) {
        errs() << "Can't map bb, out of registers!" << "\n";
    }
    
    // utilization of pe resources.
    idiv_pes = pe_len * pe_len * d_ratio * i_ratio / dmal_total / fi_total - idiv_pes;
    imul_pes = pe_len * pe_len * m_ratio * i_ratio / dmal_total / fi_total - imul_pes;
    iari_pes = pe_len * pe_len * a_ratio * i_ratio / dmal_total / fi_total - iari_pes;
    ilog_pes = pe_len * pe_len * l_ratio * i_ratio / dmal_total / fi_total - ilog_pes;
    fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total - fdiv_pes;
    fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total - fmul_pes;
    fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total - fari_pes;
    flog_pes = pe_len * pe_len * l_ratio * f_ratio / dmal_total / fi_total - flog_pes;
    mem_units = (pe_len + 1) * (pe_len + 1) - mem_units;
    if (!fail) {
        errs() << "Basic block can be mapped with " << 
            idiv_pes << "," << imul_pes << "," << iari_pes << "," <<
            fdiv_pes << "," << fmul_pes << "," << fari_pes << "," <<
            ilog_pes << "," << flog_pes << "," << mem_units << "\n" ;
    }
    
    return true;
}

bool StiltonPass::initialize(Module &M)
{
    return true;
}

bool StiltonPass::finialize(Module &M)
{
    return true;
}

char StiltonPass::ID = 0;

// Register the pass so `opt -stilton` runs it.
static RegisterPass<StiltonPass> X("stilton", "a simple allocation pass");
