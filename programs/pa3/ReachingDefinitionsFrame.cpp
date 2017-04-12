#include "ReachingDefinitionsFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

using namespace llvm;

ReachingDefinitionsFrame::ReachingDefinitionsFrame(Function* scope, bool dir, bool init):DataFlowFrame(scope, dir, init){};


void ReachingDefinitionsFrame::genFunction(const Instruction* ins, SetVector<StringRef>* genSet)
{
    genSet->insert(ins->getName());
#if PRINT_PASS_DEBUG            
    outs() << "\n gen function " << ins->getName();
#endif   
}

void ReachingDefinitionsFrame::killFunction(const Instruction* ins, SetVector<StringRef>* killSet)
{
    killSet->insert(ins->getName());
#if PRINT_PASS_DEBUG            
    outs() << "\n kill function " << ins->getName();
#endif    
}
bool ReachingDefinitionsFrame::meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out, vector<SetVector<StringRef>*>* prev)
{
#if PRINT_PASS_DEBUG    
    static int i;
    outs() << "meet" << i++ << "\n";
#endif 
    bool change = false;

    for(int i = 0; i < (int)prev->size(); i++)
    {
        for(auto j = ((*prev)[i])->begin(); j != ((*prev)[i])->end(); j++)
        {
                change |= in->insert(*j);     
#if PRINT_PASS_DEBUG                
        outs() << " " << *j << "\n";
#endif              
        }
    }        
    
    return change;
}
bool ReachingDefinitionsFrame::transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out)
{
#if PRINT_PASS_DEBUG        
    static int i;
    outs() << "transfer" << i++ << "\n";    
#endif   
    bool change = false;
    for(auto g = gen->begin(); g != gen->end(); g++)
    {
        change |= out->insert(*g);
#if PRINT_PASS_DEBUG                
        outs() << " " << *g << "\n";
#endif        
    }
    for(auto i = in->begin(); i != in->end(); i++)
    {
        if(find(kill->begin(), kill->end(), *i) == kill->end())
        {
            change |= out->insert(*i);
#if PRINT_PASS_DEBUG                
        outs() << " " << *i << "\n";
#endif              
        }
    }    
   
    return change;
}
void ReachingDefinitionsFrame::unionSet(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1)
{
    for(auto it = dom1->begin(); it != dom1->end(); it++)
    {
        dom0->insert(*it);   
    } 
}

void ReachingDefinitionsFrame::boundaryCondition(SetVector<StringRef>* boundSet, Function* scope)
{
    for(auto a = scope->getArgumentList().begin(); a != scope->getArgumentList().end(); a++)
    {
        boundSet->insert(a->getName());
    }    
}

void ReachingDefinitionsFrame::handlePrevPhi(SetVector<StringRef>* PhiInSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB) // only necessary for backwards analysis
{         
   // do nothing
}


void ReachingDefinitionsFrame::emptySet(SetVector<StringRef>* dom)
{
    // do nothing
}           

ReachingDefinitionsFrame::~ReachingDefinitionsFrame(){};