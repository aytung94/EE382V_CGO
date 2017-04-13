#include "reach.h"
#include "ReachingDefinitionsFrame.h"
#include "DataFlowAnnotator.h"

#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringSet.h>

using namespace llvm;
using namespace example;

bool reach::runOnFunction(Function& F)
{      
    ReachingDefinitionsFrame reaching(&F, true, false);         
    reaching.createDataFlow();
   
    DataFlowAnnotator<ReachingDefinitionsFrame> annotator(reaching, errs());
    annotator.print(F);
        
    return false;
} 

void reach::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char reach::ID = 0;

// Register the pass name to allow it to be called with opt:
// See http://llvm.org/releases/3.9.1/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
static RegisterPass<reach> X("reach", "reaching analysis");
