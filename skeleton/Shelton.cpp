#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instruction.h"
#include <list>
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
    virtual bool checkInstrNotInUsed(std::list<Instruction*> Used, Instruction &I);
    virtual bool checkInstrDependence(std::list<Instruction*> Deps, Instruction &I);
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
  std::list<Instruction*> Deps; 
  std::list<Instruction*> Used; 
  for (auto &B: F) {
      errs() << "\n BB size: " << B.size() << "\n";
      for (auto &I: B) {
          errs() << "\n Instruction: " << I << "\n";
          if (checkInstrNotInUsed(Used, I)) {
            Deps.push_back(&I);
          }
          if (checkInstrDependence(Deps, I)) {
            Used.push_back(&I);
          }
      }
  }
  errs() << "\n Deps size: " << Deps.size() << "\n";
  errs() << "\n Used size: " << Used.size() << "\n";
  return false;
}

bool SheltonPass::checkInstrNotInUsed(std::list<Instruction*> Used, Instruction &I) {
    for (auto U: Used) {
        if (U == &I) {
            return false;
        }
    }
    return true;
}

bool SheltonPass::checkInstrDependence(std::list<Instruction*> Deps, Instruction &I) {
    for (auto D: Deps) {
        for (auto& U : D->uses()) {
            User* user = U.getUser();
            if (user == &I) {
                return false;
            }
        }
    }
    return true;
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
