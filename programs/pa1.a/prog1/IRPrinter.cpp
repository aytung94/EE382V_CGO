#include "IRPrinter.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/AssemblyAnnotationWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/IR/DebugInfo.h>

using namespace llvm;
using namespace ee382v;

bool IRPrinter::runOnModule(Module& M)
{
	// Remove the following line and before you write down your own codes
//	M.print(outs(), nullptr);

    for(Module::iterator myFunctionIterator = M.begin(); myFunctionIterator != M.end(); myFunctionIterator++)
    {
        // Prototype or Definition?
        bool isProto;
        if(myFunctionIterator->isDeclaration())
        {
            isProto = true;
            outs() << "declare ";
        }
        else 
        {
            isProto = false;
            outs() << "define ";
        }

        // Return Type
        myFunctionIterator->getReturnType()->print(outs(), false, false);
        outs() << " ";

        // Name
        outs() << "@" << myFunctionIterator->getName();

        // Arguments
        outs() << "(";
        for(Function::arg_iterator myArgumentIterator = myFunctionIterator->arg_begin(); 
            myArgumentIterator != myFunctionIterator->arg_end(); myArgumentIterator++)
        {       
            if(myArgumentIterator != myFunctionIterator->arg_begin())
            {
                outs() << ", ";
            }
            myArgumentIterator->getType()->print(outs());                       
        }
        if(myFunctionIterator->isVarArg())
        {
            outs() << ", ...";
        }
        outs() << ")";
        
        // Proto or Def ends
        if(isProto)
            outs() << ";";
        else
            outs() << "{";
        

        // Basic Blocks
        for(Function::iterator myBasicBlockIterator = myFunctionIterator->begin(); 
            myBasicBlockIterator != myFunctionIterator->end(); myBasicBlockIterator++)
        {
            // Has label name or not?
            if(myBasicBlockIterator->hasName())
            {
                outs() << "\n" <<  myBasicBlockIterator->getName() << ":";   
            }
            else
            {
                outs() << "\n; <label>: ";
                myBasicBlockIterator->printAsOperand(outs(), false); 
            }
            outs() << "\n";

            // Instructions
            for(BasicBlock::iterator myInstructionIterator = myBasicBlockIterator->begin();
                myInstructionIterator != myBasicBlockIterator->end(); myInstructionIterator++)
            {
                // Print source code line number
                if (myInstructionIterator->getDebugLoc()) { // Here I is an LLVM instruction
                    uint32_t line = (myInstructionIterator->getDebugLoc())->getLine();
                    fouts() << line << " ";
                }
                myInstructionIterator->dump();
            }        
        }

        // Make room for next function
        if(!isProto)
            outs() << "}";
        outs() << "\n\n";
    }

	return false;
} 
void IRPrinter::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.setPreservesAll();
}

// LLVM uses the address of this static member to identify the pass, so the
// initialization value is unimportant.
char IRPrinter::ID = 0;

// Register the pass name to allow it to be called with opt:
// See http://llvm.org/releases/3.9.1/docs/WritingAnLLVMPass.html#running-a-pass-with-opt for more info.
static RegisterPass<IRPrinter> X("printIR", "IR + Source line number printer");
