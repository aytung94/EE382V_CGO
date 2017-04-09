#include "DataFlowFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

#define PRINT_INSTRUCTION   1

using namespace llvm;
using namespace std;

class LivenessFrame: public DataFlowFrame<SetVector<StringRef>, Function, Instruction>
{
private:     
    
public:     
    LivenessFrame(Function* scope, bool dir, bool init):DataFlowFrame(scope, dir, init){};
   
    // User defined functions   
    void genFunction(Instruction* ins, SetVector<StringRef>* genSet);
    void killFunction(Instruction* ins, SetVector<StringRef>* killSet);
    bool meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out);    
    bool transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out);
    void unionDomain(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1);
    void emptyDomain(SetVector<StringRef>* dom);
    ~LivenessFrame();     
};
