#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/Format.h"
#include <unordered_map>
#include <vector>

#define PRINT_GEN_DEBUG   0
#define PRINT_PASS_DEBUG  0

using namespace llvm;
using namespace std;

template <typename Domain, typename Point> 
class DataFlowFrame
{
private:
    Function* F;
    bool Dir, Init;    
    unordered_map<const Instruction*, Domain> inSets;
    unordered_map<const Instruction*, Domain> outSets;
    unordered_map<const Instruction*, Domain> genSets;
    unordered_map<const Instruction*, Domain> killSets;	   
    unordered_map<const Instruction*, vector<const Instruction*>> prevIns;

public:

    // User defined functions   
    virtual void genFunction(const Instruction* ins, Domain* genSet) = 0;
    virtual void killFunction(const Instruction* ins, Domain* killSet) = 0;
    virtual bool meetFunction(Domain* in, Domain* out, vector<Domain>* prev) = 0;    
    virtual bool transferFunction(Domain* gen, Domain* kill, Domain* in, Domain* out) = 0;
    
    virtual void unionSet(Domain* dom0, Domain* dom1) = 0;
    virtual void boundaryCondition(Domain* boundSet, Function* func) = 0;    
    virtual void handlePhi(Domain* PhiSet, const PHINode* Phi, const BasicBlock* BBtoPhiBB) = 0;
    // create a prevSet (succesors's inSets) for instructions with PHI successors for backwards
    virtual void emptySet(Domain* dom) = 0;
    virtual ~DataFlowFrame(){};

    DataFlowFrame(Function* func, bool dir, bool init):F(func), Dir(dir), Init(init){};
    
    void createDataFlow()
    {
        // INITIALIZATION PASS
        // create gen, kill, and init flow sets and prev instruction based on flow
        Domain initSet;
        emptySet(&initSet);
        for(auto B_it = F->begin(); B_it != F->end(); B_it++)
        {                                
#if (PRINT_GEN_DEBUG || PRINT_PASS_DEBUG)
            outs() << *B_it;
#endif                       
            for(auto I_it = B_it->begin(); I_it != B_it->end(); I_it++)
            {                      
                const Instruction *I = &*I_it;
                
                // init gen and kill sets
                genFunction(I, &genSets[I]);
                killFunction(I, &killSets[I]);
            
                // init set for initial flow
                if(Init)
                {                  
                    unionSet(&initSet, &genSets[I]);
                }           
            }                                                   
        }           
#if PRINT_GEN_DEBUG
                outs() << "\n";
#endif                 

        if(Dir)
        {
            for(auto B_it = F->begin(); B_it != F->end(); B_it++)
            {              
                // create previous instructions (predecessor instructions)
                vector<const Instruction*> tempVect;
                for(auto prev_B_it = pred_begin(&*B_it); prev_B_it != pred_end(&*B_it); prev_B_it++){               
                    tempVect.push_back(&*(--((*prev_B_it)->end())));                        
#if PRINT_GEN_DEBUG
                    (--((*prev_B_it)->end()))->dump();
#endif                        
                }   
                prevIns[&*(B_it->begin())] = tempVect;
                inSets[&*B_it->begin()] = initSet;
                outSets[&*B_it->begin()] = initSet;                    
                
                const Instruction* prevI = &*B_it->begin();
                for(auto I_it = ++B_it->begin(); I_it != B_it->end(); I_it++)
                {                      
                    const Instruction *I = &*I_it;

                    vector<const Instruction*> tempVect2;                             
                    tempVect2.push_back(prevI);
                    
                    prevIns[I] = tempVect2;                          
                    inSets[I] = initSet;
                    outSets[I] = initSet;
#if PRINT_GEN_DEBUG
                    prevI->dump();
#endif                                          
                    prevI = I;                        
                }           
            }
            
            Domain boundSet;
            boundaryCondition(&boundSet, F);
            
            inSets[&*(F->begin()->begin())] = boundSet; 
#if PRINT_GEN_DEBUG                            
            outs() << "forward initSet\n{ ";
            for (auto v: inSets[&*(F->begin()->begin())])
                outs() << v << " ";
            outs() << "}";
#endif                                                  
            
        }
        else
        {
            auto B_it = F->end(); 
            while(B_it != F->begin())
            {              
                --B_it;
                
                // create previous instructions (successor instructions)
                vector<const Instruction*> tempVect1;
                for(auto prev_B_it = succ_begin(&*B_it); prev_B_it != succ_end(&*B_it); prev_B_it++){              
                    auto i_it = ((*prev_B_it)->begin());
                    tempVect1.push_back(&*i_it);                        
#if PRINT_GEN_DEBUG
                    ((*prev_B_it)->begin())->dump();
#endif                        
                }   
                prevIns[&*(--(B_it->end()))] = tempVect1;
                outSets[&*(--(B_it->end()))] = initSet;
                inSets[&*(--(B_it->end()))] = initSet;                    
                
                const Instruction* prevI = &*--B_it->end();
                auto I_it = --B_it->end(); 
                while(I_it != B_it->begin())
                {                      
                    --I_it;
                    const Instruction *I = &*I_it;

                    vector<const Instruction*> tempVect2;                             
                    tempVect2.push_back(prevI);
                    
                    prevIns[I] = tempVect2;                          
                    outSets[I] = initSet;
                    inSets[I] = initSet;

#if PRINT_GEN_DEBUG
                    prevI->dump();
#endif                                          
                    prevI = I;                        
                }           
            }        
            
            Domain boundSet;
            boundaryCondition(&boundSet, F);
            
            outSets[&*(--(--F->end())->end())] = boundSet;                 
        }
#if PRINT_GEN_DEBUG                
        for(auto B_it = F->begin(); B_it != F->end(); B_it++)
        {
            for(auto I_it = B_it->begin(); I_it != B_it->end(); I_it++)
            {                                      
                for(auto i = 0; i < (int)prevIns[&*I_it].size(); i++)
                {
                    prevIns[&*I_it][i]->dump();
                }
            }
        }
#endif            

#if PRINT_GEN_DEBUG                         
        outs() << "CREATION PASS\n";
#endif             
        bool change;            
        if(Dir)
        {                
            do
            {
                change = false;
                for(auto B_it = F->begin(); B_it != F->end(); B_it++)
                {                                      
                    for(auto I_it = B_it->begin(); I_it != B_it->end(); I_it++)
                    {                      
                        const Instruction *I = &*I_it;
                        
                        // create predecessor set
                        vector<Domain> prevDoms;
                        Domain phiOutSet;     
                        // if not between basic block transitions...

                        for(int i = 0; i < (int)prevIns[I].size(); i++)
                        {                                             
                            prevDoms.push_back(outSets[prevIns[I][i]]);
                        }                                                              
                        
                        change |= meetFunction(&inSets[I], &outSets[I], &prevDoms);
                        change |= transferFunction(&genSets[I], &killSets[I], &inSets[I], &outSets[I]);
                    }           
                }
            } while(change);
        }
        else
        {
            do
            {
                change = false;
                auto B_it = F->end(); 
                while(B_it != F->begin())
                {              
                    --B_it;              
                    
                    auto I_it = B_it->end(); 
                    while(I_it != B_it->begin())
                    {                      
                        --I_it;
                        const Instruction *I = &*I_it;
    
                        // create successor set
                        vector<Domain> prevDoms; 
                        Domain phiInSet;
                        
                        if(prevIns[I].size() == 0){
                            // do nothing (TODO return empty set? nahhh?)
                        }
                        else if(prevIns[I][0]->getParent() == &*I_it->getParent())
                        {
                            prevDoms.push_back(inSets[prevIns[I][0]]); // should only be one because it is gurantee if you are instructions in the same basic block...            
                        }
                        else
                        {
                            // TODO: handle transitions between BB not Phi nodes particularly
                            // handleBBTransitions(prevIns*, )                             
                            
                            for(int i = 0; i < (int)prevIns[I].size(); i++)
                            {   
                                // if successors is a phi node
                                if(const PHINode* P = dyn_cast<PHINode>(prevIns[I][i]))
                                {
                                    if(I_it == --B_it->end()) // if last instruction of block then, rather than at multiple phis of beginning block
                                    {
                                        phiInSet = inSets[prevIns[I][i]];
                                        handlePhi(&phiInSet, P, &*B_it);
                                    
                                        prevDoms.push_back(phiInSet);
                                    }
                                    else
                                    {
                                        prevDoms.push_back(inSets[prevIns[I][i]]);   
                                    }
                                }       
                                else
                                {                                
                                    prevDoms.push_back(inSets[prevIns[I][i]]);
                                }
                            }                        
                        }
                            
                        change |= meetFunction(&inSets[I], &outSets[I], &prevDoms);
                        change |= transferFunction(&genSets[I], &killSets[I], &inSets[I], &outSets[I]);    
                    }                               
                }        
            } while(change);
        }
    }              

    Domain& getInState(Point* pnt)
    {
        if(const BasicBlock* B = dyn_cast<BasicBlock>(pnt))
        {
            return inSets[&*B->begin()];
        }
        else if(const Instruction* I = dyn_cast<Instruction>(pnt))
        {
            return inSets[I];
        }
        else
        {
            // broken, returning to avoid warnings 
            return inSets[0];            
        }
    }
    
    Domain& getOutState(Point* pnt)
    {   
        if(const BasicBlock* B = dyn_cast<BasicBlock>(pnt))
        {
            return outSets[&*--B->end()];
        }
        else if(const Instruction* I = dyn_cast<Instruction>(pnt))
        {       
            return outSets[I];
        }
        else
        {
            // broken, returning to avoid warnings 
            return outSets[0];            
        }
    }      
};
