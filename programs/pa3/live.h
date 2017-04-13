#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringSet.h>

using namespace llvm;

class live: public FunctionPass
{
private:     
    
public: 
	static char ID;         
    live() : FunctionPass(ID){};

    bool runOnFunction(Function&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;     
};
