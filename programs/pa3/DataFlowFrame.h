#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <unordered_map>

#define PRINT_INSTRUCTION   1

using namespace llvm;
using namespace std;

template <typename Domain, typename Scope, typename Point> 
class DataFlowFrame
{
private:
	Scope* Sco;
    bool Dir, Init;
    unordered_map<Instruction*, Domain*> inSets;
    unordered_map<Instruction*, Domain*> outSets;
    unordered_map<Instruction*, Domain*> genSets;
    unordered_map<Instruction*, Domain*> killSets;	
    
public:
    //virtual static char ID;
    DataFlowFrame(Scope* scope, bool dir, bool init):Sco(scope), Dir(dir), Init(init)
    {
    // use switch case without breaks to implement scope size... TODO just function... jk... it works. must change where each pass is located                   
        /*if(const Function *F = dyn_cast<Function>(scope))
        {      
            // INITIALIZATION PASS
            // create gen, kill, and init flow sets
            Domain initSet;
            emptySet(&initSet);
            for(auto B_it = F->begin(); B_it != F->begin(); B_it++)
            {
                for(auto I_it = B_it->begin(); I_it != B_it->end(); I_it++)
                {                      
                    const Instruction *I = &*I_it;
                    
                    // init gen and kill sets
                    genFunction(I, &genSets[I]);
                    killFunction(I, &killSets[I]);
                
                    // init set for initial flow
                    if(init)
                    {                  
                        unionDomain(&initSet, &genSets[I]);
                    }    
                }
            }
            for(auto B_it = F->begin(); B_it != F->begin(); B_it++)
            {              
                for(auto I_it = B_it->begin(); I_it != B_it->end(); I_it++)
                {                      
                    const Instruction *I = &*I_it;
                    
                    inSets[I] = initSet;
                    outSets[I] = initSet;
                }           
            }
            
            // CREATION PASS
            // iterate over desired analysis direction
            auto B_it_start = (Dir == 1 ? F->begin() : --F->end()); 
            auto B_it_end   = (Dir == 1? F->end() : F->begin());                                         
            // iterate again 
            bool change = false;            
            do
            {          
                // iterate over Basic Blocks
                auto B_it = B_it_start; 
                while(B_it != B_it_end)
                {                    
                    auto I_it_start = (Dir == 1? B_it->begin() : --B_it->end()); 
                    auto I_it_end   = (Dir == 1? B_it->end() : B_it->begin());    
                
                    // iterate over Instructions
                    auto I_it = I_it_start;
                    while(I_it != I_it_end)
                    {                      
                        const Instruction *I = &*I_it;                        
                        change  = meetFunction(inSets[I], outSets[I]);
                        change |= transferFunction(genSets[I], killSets[I], inSets[I], outSets[I]);
    #if PRINT_INSTRUCTION                        
                        I_it->dump();
    #endif
                        I_it = I_it + Dir;
                    }                        
                    if(Dir == -1){
                        const Instruction *I = &*I_it;                        
                        change  = meetFunction(inSets[I], outSets[I]);
                        change |= transferFunction(genSets[I], killSets[I], inSets[I], outSets[I]);
    #if PRINT_INSTRUCTION                        
                        I_it->dump();
    #endif
                        }
                        B_it = B_it + Dir;
                    }
                    if(Dir == -1)
                    {
                        auto I_it_start = (Dir == 1? B_it->begin() : --B_it->end()); 
                        auto I_it_end   = (Dir == 1? B_it->end() : B_it->begin());    
                    
                        // iterate over Instructions
                        auto I_it = I_it_start;
                        while(I_it != I_it_end)
                        {                      
                            const Instruction *I = &*I_it;                        
                            change  = meetFunction(inSets[I], outSets[I]);
                            change |= transferFunction(genSets[I], killSets[I], inSets[I], outSets[I]);
    #if PRINT_INSTRUCTION                        
                            I_it->dump();
    #endif
                            I_it = I_it + Dir;
                        }                        
                        if(Dir == -1){
                            const Instruction *I = &*I_it;                        
                            change  = meetFunction(inSets[I], outSets[I]);
                            change |= transferFunction(genSets[I], killSets[I], inSets[I], outSets[I]);
    #if PRINT_INSTRUCTION                        
                            I_it->dump();
    #endif
                    }
                }
            } while(change);
        }         */
        outs() << "hello";
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
            outs() << " in state broken";
        }
    }
    
    Domain& getOutState(Point* pnt)
    {   
        if(const BasicBlock* B = dyn_cast<BasicBlock>(pnt))
        {
            return outSets[&*B->rbegin()];
        }
        else if(const Instruction* I = dyn_cast<Instruction>(pnt))
        {       
            return outSets[I];
        }
        else
        {
            outs() << " out state broken";
        }        
    }   
    
    // User defined functions   
    virtual void genFunction(Instruction* ins, Domain* genSet) = 0;
    virtual void killFunction(Instruction* ins, Domain* killSet) = 0;
    virtual bool meetFunction(Domain* in, Domain* out) = 0;    
    virtual bool transferFunction(Domain* gen, Domain* kill, Domain* in, Domain* out) = 0;
    virtual void unionDomain(Domain* dom0, Domain* dom1) = 0;
    virtual void emptyDomain(Domain* dom) = 0;
    virtual ~DataFlowFrame() = 0;     
};
