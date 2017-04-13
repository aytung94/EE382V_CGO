#include "live.h"
#include "LivenessFrame.h"
#include "DataFlowAnnotator.h"

#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringSet.h>

using namespace llvm;
using namespace example;

bool live::runOnFunction(Function& F)
{
    LivenessFrame liveness(&F, false, false);         
    liveness.createDataFlow();
   
    DataFlowAnnotator<LivenessFrame> annotator(liveness, errs());
    annotator.print(F);
        
    return false;
} 

void live::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char live::ID = 0;

// Register the pass name to allow it to be called with opt:
// See http://llvm.org/releases/3.9.1/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
static RegisterPass<live> X("live", "liveness analysis");
