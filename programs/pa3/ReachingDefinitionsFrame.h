#include "DataFlowFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/IR/Value.h>

#define PRINT_INSTRUCTION   1

using namespace llvm;
using namespace std;

class ReachingDefinitionsFrame: public DataFlowFrame<SetVector<Value*>, const BasicBlock>
{
private:     

public:     
    ReachingDefinitionsFrame(Function* func, bool dir, bool init);
   
    // User defined functions   
    void genFunction(const Instruction* ins, SetVector<Value*>* genSet);
    void killFunction(const Instruction* ins, SetVector<Value*>* killSet);
    bool meetFunction(SetVector<Value*>* in, SetVector<Value*>* out, vector<SetVector<Value*>>* prev);
    bool transferFunction(SetVector<Value*>* gen, SetVector<Value*>* kill, SetVector<Value*>* in, SetVector<Value*>* out);

    void unionSet(SetVector<Value*>* dom0, SetVector<Value*>* dom1);
    void boundaryCondition(SetVector<Value*>* boundSet, Function* scope);
    void handlePhi(SetVector<Value*>* PhiSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB);
    void emptySet(SetVector<Value*>* dom);
    
    ~ReachingDefinitionsFrame();     
};
