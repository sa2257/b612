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
  struct StiltonPass : public ModulePass {
      static char ID;
      StiltonPass() : ModulePass(ID) {}
      
      virtual bool runOnModule(Module &M); //when there is a Module
      virtual bool runOnFunction(Function &F, Module &M); //called by runOnModule
      virtual bool runOnBasicBlock(BasicBlock &BB, Module &M); // called by runOnFunction
      
      bool initialize(Module &M); //create global variable
      bool finialize(Module &M); //print global variable
      void createInstr(BasicBlock &bb, Constant *counter_ptr, int num, bool loc);

      int d_ratio = 1; int m_ratio = 1; int a_ratio = 3; int l_ratio = 4;
      int f_ratio = 0; int i_ratio = 1;
      int dmal_total = d_ratio + m_ratio + a_ratio + l_ratio;
      int fi_total = f_ratio + i_ratio;
      int pe_len = 3;
      //int d_ratio = 1; int m_ratio = 3; int a_ratio = 4; int l_ratio = 8;
      //int f_ratio = 0; int i_ratio = 1;
      //int dmal_total = d_ratio + m_ratio + a_ratio + l_ratio;
      //int fi_total = f_ratio + i_ratio;
      //int pe_len = 4;
  };
}

bool StiltonPass::runOnModule(Module &M)
{
    bool modified = initialize(M);
    
    errs() << "Pass run status: " << SwitchOn << "\n";
    errs() << "Pass running on: " << InputModule << "\n";
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
    int fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total;
    int fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total;
    int fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total;
    int logi_pes = pe_len * pe_len * l_ratio / dmal_total;
    int ld_units = 5 * 4 + (pe_len - 2) * 4 * 3;
    int st_units = 5 * 4 + (pe_len - 2) * 4 * 3;
    int other = 0;
    bool idiv = idiv_pes > 0 ? true : false; bool fdiv = fdiv_pes > 0 ? true : false;
    bool imul = imul_pes > 0 ? true : false; bool fmul = fdiv_pes > 0 ? true : false;
    bool iari = iari_pes > 0 ? true : false; bool fari = fari_pes > 0 ? true : false;
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
                logi_pes--;
                continue;
            case Instruction::Or: // or
                logi_pes--;
                continue;
            case Instruction::Xor: // xor
                logi_pes--;
                continue;
            case Instruction::Br: // branch
                continue;
            case Instruction::Switch: // switch
                continue;
            case Instruction::Store: // store
                st_units--;
                continue;
            case Instruction::Load: // load
                ld_units--;
                continue;
            case Instruction::Alloca: // allocate stack memory
                ld_units--;
                continue;
            case Instruction::Ret: // Ignore return
                continue;
            default:
                errs() << "Can't map bb, instruction " << it->getOpcodeName() << " not supported!" << "\n";
                fail = true;
                break;
        }

        if(idiv && idiv_pes == 0) {
            errs() << "Can't map bb, out of idiv resources!" << "\n";
            fail = true;
            break;
        } else if(imul_pes == 0) {
            errs() << "Can't map bb, out of imul resources!" << "\n";
            fail = true;
            break;
        } else if(iari_pes == 0) {
            errs() << "Can't map bb, out of iari resources!" << "\n";
            fail = true;
            break;
        } else if(fdiv && fdiv_pes == 0) {
            errs() << "Can't map bb, out of fdiv resources!" << "\n";
            fail = true;
            break;
        } else if(fmul && fmul_pes == 0) {
            errs() << "Can't map bb, out of fmul resources!" << "\n";
            fail = true;
            break;
        } else if(fari && fari_pes == 0) {
            errs() << "Can't map bb, out of fari resources!" << "\n";
            fail = true;
            break;
        } else if(logi_pes == 0) {
            errs() << "Can't map bb, out of logi resources!" << "\n";
            fail = true;
            break;
        } else if(ld_units == 0) {
            errs() << "Can't map bb, out of load slots!" << "\n";
            fail = true;
            break;
        } else if(st_units == 0) {
            errs() << "Can't map bb, out of store slots!" << "\n";
            fail = true;
            break;
        }
    }

    // utilization of pe resources.
    idiv_pes = pe_len * pe_len * d_ratio * i_ratio / dmal_total / fi_total - idiv_pes;
    imul_pes = pe_len * pe_len * m_ratio * i_ratio / dmal_total / fi_total - imul_pes;
    iari_pes = pe_len * pe_len * a_ratio * i_ratio / dmal_total / fi_total - iari_pes;
    fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total - fdiv_pes;
    fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total - fmul_pes;
    fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total - fari_pes;
    logi_pes = pe_len * pe_len * l_ratio / dmal_total - logi_pes;
    ld_units = 5 * 4 + (pe_len - 2) * 4 * 3 - ld_units;
    st_units = 5 * 4 + (pe_len - 2) * 4 * 3 - st_units;
    if (!fail) {
        errs() << "Basic block can be mapped with " << 
            idiv_pes << "," << imul_pes << "," << iari_pes << "," <<
            fdiv_pes << "," << fmul_pes << "," << fari_pes << "," <<
            logi_pes << "," << ld_units << "," << st_units << "\n" ;
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
