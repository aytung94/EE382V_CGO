#define DEBUG_TYPE "InstrumentPass"

#include "InstrumentPass.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace ee382v;
using namespace llvm;
using namespace std;

// User macros
#define PRINT_DEBUG 1
#define USE_GETBLOCKS 1

// User defined datatypes
typedef SmallVector<BasicBlock*, 32> block_vector;
typedef unordered_set<BasicBlock*> block_set;
typedef unordered_map<BasicBlock*, int> block_map;
typedef unordered_map<BasicBlock*, block_map> block_graph;
typedef stack<BasicBlock*> block_stack;

// Instrument global variables
int loopId = 1;
unordered_map<int, unordered_map<int, int>> path_profile;
unordered_map<int, int> r;
void createPath(block_vector& reverseOrder, block_map& numPaths, block_graph& pathGraph, block_set& visited, Loop& loop, BasicBlock& header, BasicBlock& node, BasicBlock& Exit);

bool InstrumentPass::runOnLoop(llvm::Loop* loop, llvm::LPPassManager& lpm)
{
    // Initialize necessary 
#if PRINT_DEBUG == 1    
if(loopId == 1)
{
    LoopInfo& loopinfo = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    loopinfo.print(outs());
    outs() << "\n";
#if USE_GETBLOCKS == 1
    outs() << "USING GETBLOCKS\n";
#endif 
}
#endif

    DominatorTree& domTree = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
    DomTreeNode *node = domTree.getNode(loop->getHeader());
    BasicBlock *header = node->getBlock();
    node = domTree.getNode(loop->getLoopLatch());
    BasicBlock *latch = node->getBlock();
    Module *MP = loop->getHeader()->getParent()->getParent();   
    LLVMContext *C = &MP->getContext();
    
    // Initialize necessary data sets
    block_vector RTO;
    block_map numPaths;
    block_graph pathGraph;
    block_set visited;

    //Insert dummy exit
    BasicBlock* Exit = BasicBlock::Create(*C, "Exit", NULL, NULL);
    numPaths.insert({Exit, 1});
    pathGraph.insert({Exit, block_map()});

    // No subloops (i.e. most inner loop)
    if(loop->empty()){

#if PRINT_DEBUG == 1
    outs() << "\n---------- DEBUG PRINT FOR LOOP " << loopId << " ----------\n";
    outs() << "INNER LOOP FOUND\n\n"; 
    outs() << "Header: ";
    header->printAsOperand(outs(), false);
    outs() << "\nLatch: ";
    latch->printAsOperand(outs(), false); 
    outs() << "\n";
#endif          
        // Get Reverse Topological Order
        createPath(RTO, numPaths, pathGraph, visited, *loop, *header, *header, *Exit); 
         
#if PRINT_DEBUG == 1
        outs() << "\nPrint Paths:\n";
        for(int i = 0; i < (int)RTO.size(); i++){
            outs() << "; <label> ";
                RTO[i]->printAsOperand(outs(), false);
                outs() << ", paths = " << numPaths[RTO[i]];

                if(loop->isLoopExiting(RTO[i]) || latch == RTO[i])
                {
                    outs() << ", exiting block";
                }            
                outs() << "\n";
        }
#endif         
    }
#if PRINT_DEBUG == 1    
    else{
        outs() << "OUTER LOOP SKIP:\n"; 
    }
   
    outs() << "\nPrint Edge Values:\n";

    for(int i = RTO.size() - 1; i >= 0; i--)
    {
        BasicBlock* v = RTO[i];
        for(auto wI = pathGraph[v].begin(); wI != pathGraph[v].end(); wI++)
        {
            v->printAsOperand(outs(), false);
            outs() << "->";            
            wI->first->printAsOperand(outs(), false);            
            outs() << ": edge value = " << wI->second << "\n";            
        }
    }

    outs() << "\nPrint Instrumentation Locations\n";    
#endif


// Set up instrumentation functions

    // Init Path Register
    Function *init = dyn_cast<Function>(MP->getOrInsertFunction("init_path_reg", Type::getVoidTy(MP->getContext()), Type::getInt32Ty(MP->getContext()), NULL));
    
    // Inc Path Register
    Function *inc = dyn_cast<Function>(MP->getOrInsertFunction("inc_path_reg", Type::getVoidTy(MP->getContext()), Type::getInt32Ty(MP->getContext()), Type::getInt32Ty(MP->getContext()), NULL));
    
    // Finalize Path Register
    Function *fin = dyn_cast<Function>(MP->getOrInsertFunction("finalize_path_reg", Type::getVoidTy(MP->getContext()), Type::getInt32Ty(MP->getContext()), NULL));

// Set up global arguments for functions    
    APInt loopID(32, loopId);   
    Value *init_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID)}; 
    Value *fin_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID)}; 

// Insert functions

    // Call Init   
    CallInst *call_init = CallInst::Create(init, init_arg_values);
    call_init->insertBefore(header->getFirstNonPHI()); 

//outs() << RTO[RTO.size()-1]->getName() << "\n"; 

    // Call Inc and Final (<-TODO: CHANGE THIS TO FUNCTION IN DFS TO PRINT APPORPRIATE OUTPUT)
    for(int i = RTO.size() - 1; i >= 0; i--)
    {
        BasicBlock* v = RTO[i]; // assumption w has one entry edge for v->w 
        for(auto wI = pathGraph[v].begin(); wI != pathGraph[v].end(); wI++)
        {   
            // Iterate over all psuedo-exit blocks by finding actual exit blocks to instrument (except latch->header)
            if(wI->first == Exit && v != latch)            
            {                    
                for(auto SuccI = succ_begin(v); SuccI != succ_end(v); SuccI++)
                {
                     if(!loop->contains(*SuccI)) // Should never see header unless latch!! guaranteed by no crit edges
                     {  
                        // Insert Call Final for Exits
                        Value *fin_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID)}; 
                        CallInst *call_fin = CallInst::Create(fin, fin_arg_values);
                        call_fin->insertBefore((llvm::Instruction *)(*SuccI)->getFirstNonPHI());  
                                               
                        // Insert Call Inc for Exits if edge value is not 0
                        if(wI->second != 0){ 
#if PRINT_DEBUG == 1                                 
                            v->printAsOperand(outs(), false);
                            outs() << "->";
                            wI->first->printAsOperand(outs(), false);            
                            outs() << ": edge value = " << wI->second << "\n";                        
#endif 
                            APInt val(32, wI->second);
                            Value *inc_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID), Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), val)}; 
                            CallInst *call_inc = CallInst::Create(inc, inc_arg_values); 
                            call_inc->insertBefore((llvm::Instruction*)((*SuccI)->getFirstNonPHI())); 
                        } 
                    }        
                }    
            }
            
            // Insert Call Inc for Internal Blocks
            else
            { 
                if(wI->second != 0){ 
#if PRINT_DEBUG == 1                                 
                    v->printAsOperand(outs(), false);
                    outs() << "->";
                    wI->first->printAsOperand(outs(), false);            
                    outs() << ": edge value = " << wI->second << "\n";                        
#endif                                         

                    APInt val(32, wI->second);
                    Value *inc_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID), Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), val)}; 
                    CallInst *call_inc = CallInst::Create(inc, inc_arg_values); 
                    call_inc->insertBefore((llvm::Instruction*)wI->first->getFirstNonPHI());
                }
            }
        }
    }


    // Call Finalize for latch
    CallInst *call_fin = CallInst::Create(fin, fin_arg_values);
    call_fin->insertBefore(latch->getTerminator());

    // Increment Loop ID TODO
    loopId++;

// PRINT INFO

    block_stack DFS;
    stack<pair<int, string>> valPaths;
    unordered_map<int, string> printPaths;

    BasicBlock* v = header;    
    string arrow = "->";

    DFS.push(v);
    valPaths.push({0, v->getName()});

    while(pathGraph.size() != 0)
    {        
        v->printAsOperand(outs(),false);
        outs() << " " << valPaths.top().first <<" " <<  valPaths.top().second << "\n";       
        for(int i = 0; i < 100; i++) 
        {
            outs() << " ";
        }
        if(v != Exit)
        {
            auto wI = pathGraph[v].begin();            
            if(wI != pathGraph[v].end())
            {
                 v = wI->first;
                 DFS.push(v);
                 if(valPaths.empty()){
                     valPaths.push({0, v->getName()});
                 }
                 else{                             
                    valPaths.push({(valPaths.top().first + wI->second), (valPaths.top().second + arrow + v->getName().str())});
                 }                 
            }
            else
            {                              
                pathGraph.erase(v);

                valPaths.pop();                

                v = DFS.top();
                DFS.pop();

                if(pathGraph.size() != 0){
                    pathGraph[DFS.top()].erase(v);
                    v = DFS.top();
                }
                else {
                    break;
                }
            }
        }
        else
        {   
            printPaths.insert({valPaths.top().first, valPaths.top().second});
            valPaths.pop();

            v = DFS.top(); DFS.pop();
            pathGraph[DFS.top()].erase(v);                        
            v = DFS.top();
        }
    }

   printf("\nLoopId: PathID: Value:\n");
   int indP = 0;
   for(auto itP = printPaths.begin(); itP != printPaths.end(); itP++){
        printf("%-6d  %-6d  %-6s\n", loopId, indP++, itP->second.c_str());  
   }



#if PRINT_DEBUG == 1
    outs() << "--------------------------------------------\n\n";
#endif    
    return false;    
}

void createPath(block_vector& reverseOrder, block_map& numPaths, block_graph& pathGraph, block_set& visited, Loop& loop, BasicBlock& header, BasicBlock& node, BasicBlock& Exit)
{
#if USE_GETBLOCKS == 0    
    for(succ_iterator SuccI = succ_begin(&node); SuccI != succ_end(&node); SuccI++)
    {
        BasicBlock *Succ = *SuccI;
#endif        
/*
        outs() << "Successors = ";
        Succ->printAsOperand(outs(), false);
        outs() << "\n";
*/
#if USE_GETBLOCKS == 0
        if(visited.find(Succ) == visited.end() && loop.contains(Succ) && Succ != &header)
        {
            visited.insert(Succ);
#endif            
/*
            outs() << "-; <label> ";
            Succ->printAsOperand(outs(), false);
            outs() << " visiting!\n";
*/
#if USE_GETBLOCKS == 0
            createPath(reverseOrder, numPaths, pathGraph, visited, loop, header, *Succ, Exit);
        }
#endif        
/*
         else if(visited.find(Succ) != visited.end())
         {
             outs() << "-Visited!\n";
         }
         else if(!loop.contains(Succ))
         {
            outs() << "-Successor not in loop!\n";
         }
         else if(Succ == &header)
         {
             outs() << "-Successor is header!\n";
         } 
        outs() << "\n";
*/
#if USE_GETBLOCKS == 0
    }
    // this happens in reverse topological order
    reverseOrder.push_back(&node); 
#endif    
   
#if USE_GETBLOCKS == 1   
    // blocks are in topological order
    vector<BasicBlock*> RTO = loop.getBlocks();
   
    for(int i = (int)RTO.size() - 1; i >= 0; i--){
        BasicBlock& node = *RTO[i];
        reverseOrder.push_back(&node); // place in reverse order
#endif

// Calculate Number of Paths
    //outs() << "\ncalculating paths\n";
    
    pathGraph.insert({&node, block_map()});
    //outs() << "path graph size = " << pathGraph[&node].size() << "\n";
    if(succ_begin(&node) == succ_end(&node))
    {
        numPaths.insert({&node, 1});
        //outs() << numPaths[&node]; 
    }
    else 
    {
        numPaths.insert({&node, 0});
        for(succ_iterator SuccI = succ_begin(&node); SuccI != succ_end(&node); SuccI++)
        {        
            BasicBlock *Succ = *SuccI;            
            if(loop.contains(Succ) && Succ != &header)
            {
                pathGraph[&node].insert({Succ, numPaths[&node]}); 
                //outs() << "path graph size = " << pathGraph[&node].size() << "\n";               
                numPaths[&node] += numPaths[Succ];     
                //outs() << numPaths[&node];
            }
            else // if exit block or latch block, assume exit
            {
                // Only add exit block once if multiple successors are exits or header
                if(pathGraph[&node].find(&Exit) == pathGraph[&node].end())
                {
                    pathGraph[&node].insert({&Exit, numPaths[&node]});
                    numPaths[&node] += numPaths[&Exit];
                }
            }
        }
    }
    //outs() << "\n";
#if USE_GETBLOCKS == 1
    }
#endif

}


void InstrumentPass::getAnalysisUsage(AnalysisUsage &AU) const
{
	AU.addRequired<LoopInfoWrapperPass>();
	AU.addRequired<DominatorTreeWrapperPass>();
	AU.addRequiredTransitive<DominatorTreeWrapperPass>();
	AU.setPreservesCFG();
}

char InstrumentPass::ID = 0;
static RegisterPass<InstrumentPass> X("epp", "Efficient Path Profiling Instrument Pass.");
