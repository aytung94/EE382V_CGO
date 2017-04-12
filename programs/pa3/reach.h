#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringSet.h>

using namespace llvm;

class reach: public ModulePass
{
private:     
    
public: 
	static char ID;         
    reach() : ModulePass(ID){};

    bool runOnModule(Module&);

	void getAnalysisUsage(llvm::AnalysisUsage &AU) const;     
};
