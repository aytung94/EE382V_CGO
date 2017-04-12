#include "LivenessFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/ADT/StringRef.h>

using namespace llvm;

LivenessFrame::LivenessFrame(Function* scope, bool dir, bool init):DataFlowFrame(scope, dir, init){};


void LivenessFrame::genFunction(const Instruction* ins, SetVector<StringRef>* genSet)
{
    if(const BranchInst* b_ins = dyn_cast<BranchInst>(ins))
    {
        if(b_ins->isConditional())
        {
            genSet->insert(b_ins->getCondition()->getName());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << b_ins->getCondition()->getName();
#endif         
        }        
    }       
    else if(const CallInst* c_ins = dyn_cast<CallInst>(ins))
    {
        for(auto a = c_ins->arg_begin(); a != c_ins->arg_end(); a++)
        {
            genSet->insert(a->get()->getName());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << a->get()->getName();
#endif        
        }        
    }
    else if(const PHINode* p_ins = dyn_cast<PHINode>(ins))
    {
        for(int p = 0; p < (int)p_ins->getNumIncomingValues(); p++)
        {
            genSet->insert(p_ins->getIncomingValue(p)->getName());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << p_ins->getIncomingValue(p)->getName();
#endif             
        }
    }
    else
    {
        for(auto v = ins->op_begin(); v != ins->op_end(); v++)
        {
            genSet->insert(v->get()->getName());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << v->get()->getName();
#endif        
        }
    }
}

void LivenessFrame::killFunction(const Instruction* ins, SetVector<StringRef>* killSet)
{
    killSet->insert(ins->getName());
#if PRINT_PASS_DEBUG            
    outs() << "\n kill function " << ins->getName();
#endif    
}
bool LivenessFrame::meetFunction(SetVector<StringRef>* in, SetVector<StringRef>* out, vector<SetVector<StringRef>*>* prev)
{
#if PRINT_PASS_DEBUG    
    static int i;
    outs() << "meet" << i++ << "\n";
#endif 
    bool change = false;

    for(int i = 0; i < (int)prev->size(); i++)
    {
        (*prev)[i]->begin();
        for(auto j = ((*prev)[i])->begin(); j != ((*prev)[i])->end(); j++)
        {
                change |= out->insert(*j);     
#if PRINT_PASS_DEBUG                
        outs() << " " << *j << "\n";
#endif              
        }
    }
    
    return change;
}
bool LivenessFrame::transferFunction(SetVector<StringRef>* gen, SetVector<StringRef>* kill, SetVector<StringRef>* in, SetVector<StringRef>* out)
{
#if PRINT_PASS_DEBUG        
    static int i;
    outs() << "transfer" << i++ << "\n";    
#endif   
    bool change = false;
    for(auto g = gen->begin(); g != gen->end(); g++)
    {
        change |= in->insert(*g);
#if PRINT_PASS_DEBUG                
        outs() << " " << *g << "\n";
#endif        
    }
    for(auto o = out->begin(); o != out->end(); o++)
    {
        if(find(kill->begin(), kill->end(), *o) == kill->end())
        {
            change |= in->insert(*o);
#if PRINT_PASS_DEBUG                
        outs() << " " << *o << "\n";
#endif              
        }
    }    
   
    return change;
}
void LivenessFrame::unionSet(SetVector<StringRef>* dom0, SetVector<StringRef>* dom1)
{
    for(auto it = dom1->begin(); it != dom1->end(); it++)
    {
        dom0->insert(*it);   
    } 
}

void LivenessFrame::boundaryCondition(SetVector<StringRef>* boundSet, Function* scope)
{
        scope->begin();
}

void LivenessFrame::handlePrevPhi(SetVector<StringRef>* PhiInSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB) // only necessary for backwards analysis
{         
    auto phi_it = Phi->getParent()->begin();
    while(const PHINode* phi_pt = dyn_cast<PHINode>(&*phi_it))
    {
        for(int e = 0; e < (int)phi_pt->getNumIncomingValues(); e++)
        {
            BasicBlock* BB = phi_pt->getIncomingBlock(e);
            if(BB != BBtoPhiBB){
                PhiInSet->remove(phi_pt->getIncomingValue(e)->getName());
            }
        }
        phi_it++;
    }
}


void LivenessFrame::emptySet(SetVector<StringRef>* dom)
{
    // do nothing
}           

LivenessFrame::~LivenessFrame(){};