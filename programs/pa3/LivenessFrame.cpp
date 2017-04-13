#include "LivenessFrame.h"

#include <llvm/IR/Module.h>
#include <llvm/ADT/SetVector.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;


LivenessFrame::LivenessFrame(Function* func, bool dir, bool init):DataFlowFrame(func, dir, init){};


void LivenessFrame::genFunction(const Instruction* ins, SetVector<Value*>* genSet)
{
    if(const BranchInst* b_ins = dyn_cast<BranchInst>(ins))
    {
        if(b_ins->isConditional())
        {
            genSet->insert(b_ins->getCondition());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << b_ins->getCondition()->getName();
#endif         
        }        
    }       
    else if(const CallInst* c_ins = dyn_cast<CallInst>(ins))
    {
        for(auto a = c_ins->arg_begin(); a != c_ins->arg_end(); a++)
        {
            genSet->insert(a->get());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << a->get()->getName();
#endif        
        }        
    }
    else if(const PHINode* p_ins = dyn_cast<PHINode>(ins))
    {
        for(int p = 0; p < (int)p_ins->getNumIncomingValues(); p++)
        {
            genSet->insert(p_ins->getIncomingValue(p));
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << p_ins->getIncomingValue(p)->getName();
#endif             
        }
    }
    else
    {
        for(auto v = ins->op_begin(); v != ins->op_end(); v++)
        {
            genSet->insert(v->get());
#if PRINT_PASS_DEBUG        
            outs() << "\n gen function " << v->get()->getName();
#endif        
        }
    }
}

void LivenessFrame::killFunction(const Instruction* ins, SetVector<Value*>* killSet)
{
    killSet->insert((Value*) ins);
#if PRINT_PASS_DEBUG            
    outs() << "\n kill function " << ins->getName();
#endif    
}
bool LivenessFrame::meetFunction(SetVector<Value*>* in, SetVector<Value*>* out, vector<SetVector<Value*>>* prev)
{
#if PRINT_PASS_DEBUG    
    static int i;
    outs() << "meet" << i++ << "\n";
#endif 
    bool change = false;

    for(int i = 0; i < (int)prev->size(); i++)
    {
        (*prev)[i].begin();
        for(auto j = ((*prev)[i]).begin(); j != ((*prev)[i]).end(); j++)
        {
                change |= out->insert(*j);     
#if PRINT_PASS_DEBUG                
        outs() << " " << *j << "\n";
#endif              
        }
    }
    
    return change;
}
bool LivenessFrame::transferFunction(SetVector<Value*>* gen, SetVector<Value*>* kill, SetVector<Value*>* in, SetVector<Value*>* out)
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
void LivenessFrame::unionSet(SetVector<Value*>* dom0, SetVector<Value*>* dom1)
{
    for(auto it = dom1->begin(); it != dom1->end(); it++)
    {
        dom0->insert(*it);   
    } 
}

void LivenessFrame::boundaryCondition(SetVector<Value*>* boundSet, Function* scope)
{
    boundSet->clear();
}

void LivenessFrame::handlePhi(SetVector<Value*>* PhiSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB) 
{         
    auto phi_it = Phi->getParent()->begin();
    while(const PHINode* phi_pt = dyn_cast<PHINode>(&*phi_it))
    {
        for(int e = 0; e < (int)phi_pt->getNumIncomingValues(); e++)
        {
            BasicBlock* BB = phi_pt->getIncomingBlock(e);
            if(BB != BBtoPhiBB){
                PhiSet->remove(phi_pt->getIncomingValue(e));
            }
        }
        phi_it++;
    }
}


void LivenessFrame::emptySet(SetVector<Value*>* dom)
{
    dom->clear();
}           

LivenessFrame::~LivenessFrame(){};