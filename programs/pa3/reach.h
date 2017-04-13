#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringSet.h>

using namespace llvm;

class reach: public FunctionPass
{
private:     
    
public: 
	static char ID;         
    reach() : FunctionPass(ID){};

    bool runOnFunction(Function&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;     
};
