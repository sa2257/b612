#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instruction.h"
using namespace llvm;

namespace {
  struct SheltonPass : public FunctionPass {
    static char ID;
    SheltonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F); // Called for every function
    virtual int runOnInstruction(Instruction &I, int depth);
    virtual bool successorsOfInstruction(Instruction &I);
  };
}

bool SheltonPass::runOnFunction(Function &F) {
  errs() << "Visiting function " << F.getName() << "!\n";
  bool analyzed = false;
  int maxDepth = 0;
  for (auto &B: F) {
      //errs() << "Basic Block: " << B << "\n";
      for (auto &I: B) {
          errs() << "Instruction: " << I << "\n";
          int depth = 1;
          //analyzed = successorsOfInstruction(I) | analyzed;
          depth = runOnInstruction(I, depth);
          if (depth > maxDepth) {
              maxDepth = depth;
          }
      }
  }
  errs() << "Maximum tree depth is " << maxDepth << "\n";
  return analyzed;
}

int SheltonPass::runOnInstruction(Instruction &I, int depth) {
  for (auto& U : I.uses()) {
      User* user = U.getUser();  // Find all the places I is used
      //errs() << "Use in function call: " << *user << "\n";
      if (isa<Instruction>(user)){
          Instruction* ins = cast<Instruction>(user);
          errs() << "Next in path: " << *ins << "\n";
          depth++;
          depth = runOnInstruction(*ins, depth);
      }
  }
  return depth;
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
