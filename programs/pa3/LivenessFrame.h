#include "DataFlowFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

using namespace llvm;
using namespace std;

class LivenessFrame: public DataFlowFrame<SetVector<StringRef>, const BasicBlock>
{
private:     
    
public:     
    LivenessFrame(Function* func, bool dir, bool init);
   
    // User defined functions   
    void genFunction(const Instruction* ins, SetVector<StringRef>* genSet);
    void killFunction(const Instruction* ins, SetVector<StringRef>* killSet);
    bool meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out, vector<SetVector<StringRef>>* prev);
    bool transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out);
    
    void unionSet(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1);
    void boundaryCondition(SetVector<StringRef>* boundSet, Function* scope);
    void handlePhi(SetVector<StringRef>* PhiSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB);
    void emptySet(SetVector<StringRef>* dom);
    
    ~LivenessFrame();     
};
