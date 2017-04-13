#include "ReachingDefinitionsFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

ReachingDefinitionsFrame::ReachingDefinitionsFrame(Function* func, bool dir, bool init):DataFlowFrame(func, dir, init){
};


void ReachingDefinitionsFrame::genFunction(const Instruction* ins, SetVector<Value*>* genSet)
{    
    genSet->insert((Value*)ins);
    
#if PRINT_PASS_DEBUG            
    outs() << "\n gen function " << ins->getName();
#endif   
}

void ReachingDefinitionsFrame::killFunction(const Instruction* ins, SetVector<Value*>* killSet)
{    
    killSet->insert((Value*)ins);
#if PRINT_PASS_DEBUG            
    outs() << "\n kill function " << ins->getName();
#endif    
      
}

bool ReachingDefinitionsFrame::meetFunction(SetVector<Value*>* in, SetVector<Value*>* out, vector<SetVector<Value*>>* prev)
{
#if PRINT_PASS_DEBUG    
    static int i;
    outs() << "meet" << i++ << "\n";
#endif 
    bool change = false;

    for(int i = 0; i < (int)prev->size(); i++)
    {
        for(auto j = ((*prev)[i]).begin(); j != ((*prev)[i]).end(); j++)
        {
                change |= in->insert(*j);     
#if PRINT_PASS_DEBUG                
        outs() << " " << *j << "\n";
#endif              
        }
    }        
    
    return change;
}

bool ReachingDefinitionsFrame::transferFunction(SetVector<Value*>* gen, SetVector<Value*>* kill, SetVector<Value*>* in, SetVector<Value*>* out)
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
            {                
                change |= out->insert(*i);
            }
#if PRINT_PASS_DEBUG                
        outs() << " " << *i << "\n";
#endif              
        }
    }    
   
    return change;
}
void ReachingDefinitionsFrame::unionSet(SetVector<Value*>* dom0, SetVector<Value*>* dom1)
{
    for(auto it = dom1->begin(); it != dom1->end(); it++)
    {
        dom0->insert(*it);   
    } 
}

void ReachingDefinitionsFrame::boundaryCondition(SetVector<Value*>* boundSet, Function* scope)
{
    for(auto a = scope->getArgumentList().begin(); a != scope->getArgumentList().end(); a++)
    {
        boundSet->insert((Value*)&*a);
    }    
}

void ReachingDefinitionsFrame::handlePhi(SetVector<Value*>* PhiSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB) 
{       
    // do nothing
}


void ReachingDefinitionsFrame::emptySet(SetVector<Value*>* dom)
{
    dom->clear();
}           

ReachingDefinitionsFrame::~ReachingDefinitionsFrame(){};