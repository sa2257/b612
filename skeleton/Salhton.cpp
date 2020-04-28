#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
using namespace llvm;


namespace {
  struct SalhtonPass : public FunctionPass {
    static char ID;
    SalhtonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
// Get the function to call from our runtime library.
		LLVMContext& Ctx = F.getContext();
		FunctionCallee logFunc = F.getParent()->getOrInsertFunction(
		  "rtlib", Type::getInt32Ty(Ctx),
          Type::getInt32Ty(Ctx), Type::getInt32Ty(Ctx)
		);
        //  Type::getInt32PtrTy(Ctx), Type::getInt32PtrTy(Ctx),
        //  Type::getInt32PtrTy(Ctx), Type::getInt32PtrTy(Ctx),
        /* create the function call */
		
		for (auto& B : F) {
		  for (auto& I : B) {
		    if (auto* op = dyn_cast<BinaryOperator>(&I)) {
		      errs() << "Insert function call after " << op->getOpcode() << "!\n";
		      IRBuilder<> builder(op);
		      builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
              /* find the place to enter the simulator call */
		
		      errs() << "Insert a call to our function!\n";
              Constant *i32_ticks = ConstantInt::get(Type::getInt32Ty(Ctx), 4, true);
		      //Value* args[] = {op->getOperand(0), op->getOperand(1), op->getOperand(2), op->getOperand(3), ticks, op->getOperand(0)};
		      Value* args[] = {i32_ticks, op->getOperand(0)};
		      Value* ret =  builder.CreateCall(logFunc, args);
		
		      for (auto& U : op->uses()) {
		          User* user = U.getUser();  // A User is anything with operands.
		          user->setOperand(U.getOperandNo(), ret);
		      }
		      
              return true;
		    }
		  }
		}

      	return false;
    }
  };
}

char SalhtonPass::ID = 0;

// Register the pass so `opt -salhton` runs it.
static RegisterPass<SalhtonPass> X("salhton", "a pass to insert a runtime insertion of a python call");
