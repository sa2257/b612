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
#include <fstream>
#include <list>

#include "llvm/Support/CommandLine.h"

using namespace std;
using namespace llvm;

static cl::opt<string> InputModule("function", cl::desc("Specify function to run pass"), cl::value_desc("module"));
static cl::opt<bool> SwitchOn("select", cl::desc("Select to run pass"));
std::ofstream outfile; // Only for static information of course! 

namespace {
  struct SingletonPass : public ModulePass {
      static char ID;
      SingletonPass() : ModulePass(ID) {}
      
      virtual bool runOnModule(Module &M); //when there is a Module
      virtual bool runOnFunction(Function &F, Module &M); //called by runOnModule
      virtual bool runOnBasicBlock(BasicBlock &BB, Module &M); // called by runOnFunction
      virtual bool mappingFunc(std::list<string> &mapping);
      
      int d_ratio = 1; int m_ratio = 1; int a_ratio = 1; int l_ratio = 1;
      int f_ratio = 1; int i_ratio = 3;
      int dmal_total = d_ratio + m_ratio + a_ratio + l_ratio;
      int fi_total = f_ratio + i_ratio;
      int pe_len = 12;
  };
}

bool SingletonPass::runOnModule(Module &M)
{
    errs() << "Pass run status: " << SwitchOn << "\n";
    errs() << "Pass running on: " << InputModule << "\n";
    outfile.open("output.txt", std::ios_base::app);
    outfile << "Pass run status: " << SwitchOn << "\n";
    outfile << "Pass running on: " << InputModule << "\n";
    
    int idiv_pes = pe_len * pe_len * d_ratio * i_ratio / dmal_total / fi_total;
    int imul_pes = pe_len * pe_len * m_ratio * i_ratio / dmal_total / fi_total;
    int iari_pes = pe_len * pe_len * a_ratio * i_ratio / dmal_total / fi_total;
    int ilog_pes = pe_len * pe_len * l_ratio * i_ratio / dmal_total / fi_total;
    int fdiv_pes = pe_len * pe_len * d_ratio * f_ratio / dmal_total / fi_total;
    int fmul_pes = pe_len * pe_len * m_ratio * f_ratio / dmal_total / fi_total;
    int fari_pes = pe_len * pe_len * a_ratio * f_ratio / dmal_total / fi_total;
    int flog_pes = pe_len * pe_len * l_ratio * f_ratio / dmal_total / fi_total;
    int mem_units = (pe_len + 1) * (pe_len + 1);
    outfile << "Available resources: " << 
        idiv_pes << "," << imul_pes << "," << iari_pes << "," <<
        fdiv_pes << "," << fmul_pes << "," << fari_pes << "," <<
        ilog_pes << "," << flog_pes << "," << mem_units << "\n" ;
    
    for (auto &func: M) {
        bool modified = runOnFunction(func, M);
    }
    
    return true;
}

bool SingletonPass::runOnFunction(Function &F, Module &M)
{
    bool modified = false;
    string funcName = F.getName();

    for (auto &bb: F) {
        if (SwitchOn || funcName == InputModule) {
            modified |= runOnBasicBlock(bb, M);
        }
    }

    return modified;
}

bool SingletonPass::runOnBasicBlock(BasicBlock &bb, Module &M)
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
    
    outfile << "Basic block of size " << bb.size() << "\n";
    std::list<string> mapping;
    for (auto &it: bb) {
        switch (it.getOpcode()) {
            case Instruction::Add: // addition
                iari_pes--;
                mapping.push_back("arith");
                continue;
            case Instruction::Sub: // subtraction
                iari_pes--;
                mapping.push_back("arith");
                continue;
            case Instruction::Mul: // multiplication
                imul_pes--;
                mapping.push_back("mul");
                continue;
            case Instruction::UDiv: // division unsigned
            case Instruction::SDiv: // division signed
                idiv_pes--;
                mapping.push_back("div");
                continue;
            case Instruction::URem: // remainder unsigned
            case Instruction::SRem: // remainder signed
                idiv_pes--;
                mapping.push_back("div");
                continue;
            case Instruction::FAdd: // fp addition
                fari_pes--;
                mapping.push_back("farith");
                continue;
            case Instruction::FSub: // fp subtraction
                fari_pes--;
                mapping.push_back("farith");
                continue;
            case Instruction::FMul: // fp multiplication
                fmul_pes--;
                mapping.push_back("fmul");
                continue;
            case Instruction::FDiv: // fp division
                fdiv_pes--;
                mapping.push_back("fdiv");
                continue;
            case Instruction::FRem: // fp remainder
                fdiv_pes--;
                mapping.push_back("fdiv");
                continue;
            case Instruction::And: // and
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::Or: // or
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::Xor: // xor
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::Trunc: // truncate
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::ZExt: // zero extend
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::SExt: // sign extend
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::Shl: // shift left
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::LShr: // logic shift right
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::AShr: // arith shift right
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::ICmp: // integer compare
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::PHI: // PHI node
                ilog_pes--;
                mapping.push_back("logic");
                continue;
            case Instruction::FCmp: // fp compare
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::FPTrunc: // fp truncate
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::FPExt: // fp extend
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::FPToUI: // fp to unsigned int
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::FPToSI: // fp to signed int
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::UIToFP: // unsigned int to fp
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::SIToFP: // signed int to fp
                flog_pes--;
                mapping.push_back("flogic");
                continue;
            case Instruction::Br: // branch
                mapping.push_back("control");
                continue;
            case Instruction::Switch: // switch
                mapping.push_back("control");
                continue;
            case Instruction::Store: // store
                mem_units--;
                mapping.push_back("memory");
                continue;
            case Instruction::Load: // load
                mem_units--;
                mapping.push_back("memory");
                continue;
            case Instruction::Call: // function call
                mem_units--;
                mapping.push_back("control");
                continue;
            case Instruction::Alloca: // Ignore allocate stack
                mapping.push_back("reg");
                continue;
            case Instruction::GetElementPtr: // Ignore get address
                continue;
            case Instruction::BitCast: // Ignore convert type without bit change
                continue;
            case Instruction::Ret: // Ignore return
                mapping.push_back("control");
                continue;
            default:
                errs() << "Can't map bb, instruction " << it.getOpcodeName() << " not supported!" << "\n";
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
        outfile << "Basic block can be mapped with " << 
            idiv_pes << "," << imul_pes << "," << iari_pes << "," <<
            fdiv_pes << "," << fmul_pes << "," << fari_pes << "," <<
            ilog_pes << "," << flog_pes << "," << mem_units << "\n" ;
    }
    
    bool mapDone = mappingFunc(mapping);
    return true;
}

bool SingletonPass::mappingFunc(std::list<string> &mapping) {
    //int i = 1;
    //for (auto S: mapping) {
    //    outfile << i << ": " << S << "\n";
    //    i++;
    //}
    
    int slcUnits  = dmal_total * fi_total;
    int noOfSlcs  = (pe_len * pe_len) / slcUnits; // assert this is int
    int insToMap  = mapping.size();

    bool mapped = false;
    int placement[noOfSlcs][dmal_total][fi_total];
    memset(placement, 0, sizeof(placement));
    
    int i = 0;
    bool mapSkip = false;
    for (int s = 0; s < noOfSlcs; s++) {
        int idivUnits = d_ratio * i_ratio;
        int imulUnits = m_ratio * i_ratio;
        int iariUnits = a_ratio * i_ratio;
        int ilogUnits = l_ratio * i_ratio;
        int fdivUnits = d_ratio * f_ratio;
        int fmulUnits = m_ratio * f_ratio;
        int fariUnits = a_ratio * f_ratio;
        int flogUnits = l_ratio * f_ratio;
        int outrUnits = 16; // Hard coding for now, should be the ones in the boundary. Outer edge of 5 x 5 grid
        int innrUnits = 9; // Inner nodes
        
        for (int j = 0; j < dmal_total; j++) {
            bool sliceSkip = false;
            for (int k = 0; k < fi_total; k++) {
                while(i < insToMap) {
                    string S = mapping.front();
                    mapping.pop_front();
                    outfile << i << ": " << S << "\n";
                    
                    if (S == "arith") {
                        if (iariUnits == 0) {
                            errs() << "Ran out of int arith units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        iariUnits--;
                        break;
                    } else if (S == "mul") {
                        if (imulUnits == 0) {
                            errs() << "Ran out of int mul units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        imulUnits--;
                        break;
                    } else if (S == "div") {
                        if (idivUnits == 0) {
                            errs() << "Ran out of int div units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        idivUnits--;
                        break;
                    } else if (S == "logic") {
                        if (ilogUnits == 0) {
                            errs() << "Ran out of int logic units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        ilogUnits--;
                        break;
                    } else if (S == "farith") {
                        if (fariUnits == 0) {
                            errs() << "Ran out of fp arith units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        fariUnits--;
                        break;
                    } else if (S == "fmul") {
                        if (fmulUnits == 0) {
                            errs() << "Ran out of fp mul units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        fmulUnits--;
                        break;
                    } else if (S == "fdiv") {
                        if (fdivUnits == 0) {
                            errs() << "Ran out of fp div units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        fdivUnits--;
                        break;
                    } else if (S == "flogic") {
                        if (flogUnits == 0) {
                            errs() << "Ran out of fp logic units to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        placement[s][j][k] = i;
                        flogUnits--;
                        break;
                    } else if (S == "control") {
                        if (innrUnits == 0) {
                            errs() << "Ran out of inner nodes to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        //placement[s][j][k] = i;
                        innrUnits--;
                        break;
                    } else if (S == "reg") {
                        if (innrUnits == 0) {
                            errs() << "Ran out of inner nodes to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        //placement[s][j][k] = i;
                        innrUnits--;
                        break;
                    } else if (S == "memory") {
                        if (outrUnits == 0) {
                            errs() << "Ran out of fp outer nodes to map!\n";
                            mapping.push_front(S);
                            sliceSkip = true;
                        }
                        //placement[s][j][k] = i;
                        outrUnits--;
                        break;
                    }
                    i++;
                }
                
                if (i == insToMap) {
                    mapSkip = true;
                }

                if (sliceSkip || mapSkip)
                    break;
                
                i++;
            }
            if (sliceSkip || mapSkip)
                break;
        }
        if (mapSkip)
            break;
    }

    if (!mapSkip) {
        errs() << "Ran out of fabric before mapping!\n";
        mapped = false;
    } else {
        for (int s = 0; s < noOfSlcs; s++) {
            outfile << "Slice: " << s << "\n";
            for (int j = 0; j < dmal_total; j++) {
                for (int k = 0; k < fi_total; k++) {
                    outfile << placement[s][j][k] << ", ";
                }
                outfile << "\n";
            }
            outfile << "\n";
        }
        mapped = true;
    }

    return mapped;
}

char SingletonPass::ID = 0;

// Register the pass so `opt -singleton` runs it.
static RegisterPass<SingletonPass> X("singleton", "a simple placement pass");
