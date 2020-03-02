#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instruction.h"
//#include <list.h>
using namespace llvm;

namespace {
  struct SheltonPass : public FunctionPass {
    static char ID;
    SheltonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F); // Called for every function
    virtual bool runDepthInFunction(Function &F);
    virtual bool runSDGInFunction(Function &F);
    
    virtual int runOnInstruction(Instruction &I, int depth);
    virtual bool successorsOfInstruction(Instruction &I);
    virtual int createSDG(Instruction &I);
    
    Instruction* SDG[20][10];
  };
}

bool SheltonPass::runOnFunction(Function &F) {
  errs() << "\n Visiting function " << F.getName() << "!\n";
  bool sdg = runSDGInFunction(F);
  //bool depth = runDepthInFunction(F);
  return false;
}

bool SheltonPass::runDepthInFunction(Function &F) {
  int maxDepth = 0;
  for (auto &B: F) {
      errs() << "\n Block: " << B << "\n";
      for (auto &I: B) {
          errs() << "\n Instruction: " << I << "\n";
          int depth = 1;
          depth = runOnInstruction(I, depth);
          if (depth > maxDepth) {
              maxDepth = depth;
          }
      }
  }
  errs() << "\n Maximum tree depth is " << maxDepth << "\n \n";
  return false;
}

bool SheltonPass::runSDGInFunction(Function &F) {
  for (auto &B: F) {
      for (auto &I: B) {
          errs() << "\n Instruction: " << I << "\n";
          int temp = createSDG(I);
      }
  }
  return false;
}

int SheltonPass::createSDG(Instruction &I) {
  int i, j;
  for (i=0; i<20; i++) {
        bool isSame = false;
    for (j=0; j<10; j++) {
        // check if SDG[i][j] is real
        for(auto& U : SDG[i][j]->uses()) { // find all places old ins is used
            User* user = U.getUser();  // find all instructions that use the old ins
            if (isa<Instruction>(user)){
                Instruction* ins = cast<Instruction>(user);
                bool isSame = ins->isIdenticalTo(&I);
                errs() << "Found current ins in " << SDG[i][j] << "\n";
                if(isSame) {
                    break;
                }
            }
        }
        if(isSame) {
            break;
        }
    }
  }
  SDG[i][j + 1] = &I;
  return 1;
}

int SheltonPass::runOnInstruction(Instruction &I, int depth) {
  int initDepth = depth;
  int maxDepth = depth; // if no uses return input depth
  for (auto& U : I.uses()) {
      depth = initDepth;
      User* user = U.getUser();  // Find all the places I is used
      if (isa<Instruction>(user)){
          Instruction* ins = cast<Instruction>(user);
          errs() << "Next in path: " << *ins << "\n";
          depth++;
          depth = runOnInstruction(*ins, depth);
          if (depth > maxDepth) {
              maxDepth = depth;
          }
      }
  }
  return maxDepth;
}

bool SheltonPass::successorsOfInstruction(Instruction &I) {
  errs() << "No. of successors " << I.getNumSuccessors() << "\n"; // Find how many successors
  if (I.getNumSuccessors() > 0) {
      BasicBlock* Succ = I.getSuccessor(0);
      errs() << "Specified successor " << *Succ << "\n";
  }
  return false;
}

char SheltonPass::ID = 0;

// Register the pass so `opt -shelton` runs it.
static RegisterPass<SheltonPass> X("shelton", "count optimal cycles");
