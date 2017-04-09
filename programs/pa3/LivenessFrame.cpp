#include "LivenessFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

using namespace llvm;

void LivenessFrame::genFunction(Instruction* ins, SetVector<StringRef>* genSet)
{
    for(auto v = ins->op_begin(); v != ins->op_end(); v++)
    {
        genSet->insert(v->get()->getName());
    }
}

void LivenessFrame::killFunction(Instruction* ins, SetVector<StringRef>* killSet)
{
    killSet->insert(ins->getName());
}
bool LivenessFrame::meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out)
{
    //for()
        // PASS IN BASIC BLOCK AND INSETS AND OUTSETS AND CREATE FOR EACH INSTRUCTION HERE
    return false;
}
bool LivenessFrame::transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out)
{
    return false;
}
void LivenessFrame::unionDomain(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1)
{
    for(auto it = dom1->begin(); it != dom1->end(); it++)
    {
        dom0->insert(*it);   
    }        
}
void LivenessFrame::emptyDomain(SetVector<StringRef>* dom)
{
    // do nothing
}           
