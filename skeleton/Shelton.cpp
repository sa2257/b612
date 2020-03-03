// Initially taken from llvm-pass-skeleton/skeleton/Skeleton.cpp at https://github.com/sampsyo/llvm-pass-skeleton.git and later modified by Sachille Atapattu

/* Shelton: Finds dependencies among instructions, create the critical path and instruction height */

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
    virtual int  runDepthInFunction(Function &F);
    virtual int  runDGInFunction(Function &F); // For each function, create the dependency graph
    virtual int  getSizeFunction(Function &F);
    
    virtual bool checkInstrNotInList(std::list<Instruction*> List, Instruction &I);
    virtual bool checkInstrDependence(std::list<Instruction*> List, Instruction &I);
    
    virtual int  runOnInstruction(Instruction &I, int depth);
  };
}

bool SheltonPass::runOnFunction(Function &F) {
  errs() << "\n Visiting function " << F.getName() << "!\n";
  //int depth = runDepthInFunction(F);
  //errs() << "\n " << F.getName() << " has " << depth << " depth!\n"; // This fails at terminators, debug
  int sdg = runDGInFunction(F);
  errs() << "\n " << F.getName() << " has " << sdg << " height!\n";
  return false;
}

/* Functions on functions */

int SheltonPass::runDepthInFunction(Function &F) {
  int maxDepth = 0;
  for (auto &B: F) {
      //errs() << "\n Block: " << B << "\n";
      for (auto &I: B) {
          int depth = 1;
          depth = runOnInstruction(I, depth);
          //errs() << "\n Instruction: " << I << " depth: " << depth << "\n";
          if (depth > maxDepth) {
              maxDepth = depth;
              errs() << "\n Path starting from Instruction: " << I << " is critical aon!\n";
          }
      }
  }
  return maxDepth;
}

int SheltonPass::runDGInFunction(Function &F) {
  std::list<Instruction*> Used;
  int height = 0;
  while (Used.size() < getSizeFunction(F)) {
    std::list<Instruction*> Deps; 
    for (auto &B: F) {
        for (auto &I: B) {
            if (checkInstrNotInList(Used, I)) {
              Deps.push_back(&I);
              if (checkInstrDependence(Deps, I)) {
                Used.push_back(&I);
                errs() << "\n Instruction: " << I << " height: " << height << "\n";
              }
            }
        }
    }
    // errs() << "\n Used size: " << Used.size() << "\n";
    height = height + 1;
  }
  return height;
}

int SheltonPass::getSizeFunction(Function &F) {
  int size = 0; 
  for (auto &B: F) {
      //errs() << "\n BB size: " << B.size() << "\n";
      size = size + B.size();
  }
  return size;
}

/* Functions on lists*/

bool SheltonPass::checkInstrNotInList(std::list<Instruction*> List, Instruction &I) {
    for (auto L: List) {
        if (L == &I) {
            return false;
        }
    }
    return true;
}

bool SheltonPass::checkInstrDependence(std::list<Instruction*> List, Instruction &I) {
    for (auto L: List) {
        for (auto& U : L->uses()) {
            User* user = U.getUser();
            if (user == &I) {
                return false;
            }
        }
    }
    return true;
}

/* Functions on instructions */

int SheltonPass::runOnInstruction(Instruction &I, int depth) {
  int initDepth = depth;
  int maxDepth = depth; // if no uses return input depth
  for (auto& U : I.uses()) {
      depth = initDepth;
      User* user = U.getUser();  // Find all the places I is used
      if (isa<Instruction>(user)){
          Instruction* ins = cast<Instruction>(user);
          //errs() << "Next in path: " << *ins << "\n";
          depth++;
          depth = runOnInstruction(*ins, depth);
          if (depth > maxDepth) {
              maxDepth = depth;
          }
      }
  }
  return maxDepth;
}

char SheltonPass::ID = 0;

// Register the pass so `opt -shelton` runs it.
static RegisterPass<SheltonPass> X("shelton", "count optimal cycles");
