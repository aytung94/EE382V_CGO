#include "DataFlowFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

#define PRINT_INSTRUCTION   1

using namespace llvm;
using namespace std;

class ReachingDefinitionsFrame: public DataFlowFrame<SetVector<StringRef>, Function, const BasicBlock>
{
private:     
    
public:     
    ReachingDefinitionsFrame(Function* scope, bool dir, bool init);//:DataFlowFrame(scope, dir, init){};
   
    // User defined functions   
    void genFunction(const Instruction* ins, SetVector<StringRef>* genSet);
    void killFunction(const Instruction* ins, SetVector<StringRef>* killSet);
    bool meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out, vector<SetVector<StringRef>*>* prev);
    bool transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out);
    void unionSet(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1);
    void handlePrevPhi(SetVector<StringRef>* PhiInSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB); // only necessary for backwards analysis
    void emptySet(SetVector<StringRef>* dom);
    ~ReachingDefinitionsFrame();     
};
