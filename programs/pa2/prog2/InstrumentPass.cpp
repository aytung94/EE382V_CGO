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

typedef SmallVector<BasicBlock*, 32> block_vector;
typedef unordered_set<const BasicBlock*> block_set;
typedef unordered_map<const BasicBlock*, int> block_map;
typedef unordered_map<const BasicBlock*, block_map> block_graph;


void revTopSortHelper(block_vector& reverseOrder, block_map& numPaths, block_graph& pathGraph, block_set& visited, Loop& loop, BasicBlock& header, BasicBlock& node)
{
    //*const TerminatorInst *TInst = node.getTerminator();
    //*int NumSucc = TInst->getNumSuccessors();
    
//DEBUG
    //*outs() << "NumSuccessors:" << NumSucc << "\n";
    //*TInst->dump();

    //*for(int i = 0; i < NumSucc; i++)
    for(succ_iterator SuccI = succ_begin(&node); SuccI != succ_end(&node); SuccI++)
    {
        //*BasicBlock *Succ = TInst->getSuccessor(i);        
        //DEBUG
        BasicBlock *Succ = *SuccI;
        outs() << "Successors = ";
        Succ->printAsOperand(outs(), false);
        outs() << "\n";

        if(visited.find(Succ) == visited.end() && loop.contains(Succ) && Succ != &header)
        {
            visited.insert(Succ);
        //DEBUG!!
        outs() << "-; <label> ";
        Succ->printAsOperand(outs(), false);
        outs() << " visiting!\n";
            revTopSortHelper(reverseOrder, numPaths, pathGraph, visited, loop, header, *Succ);
        }
        // DEBUG!!!
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
    }
    // this happens in reverse topological order
    reverseOrder.push_back(&node); 

 
// Calculate Number of Paths
    outs() << "\ncalculating paths\n";
    pathGraph.insert({&node, block_map()});
    //outs() << "path graph size = " << pathGraph[&node].size() << "\n";
    if(succ_begin(&node) == succ_end(&node))
    {
        numPaths.insert({&node, 1});
        outs() << numPaths[&node]; 
    }
    else 
    {
        numPaths.insert({&node, 0});
        bool validSucc = false;
        for(succ_iterator SuccI = succ_begin(&node); SuccI != succ_end(&node); SuccI++)
        {        
            BasicBlock *Succ = *SuccI;            
            if(loop.contains(Succ) && Succ != &header)
            {
                pathGraph[&node].insert({Succ, numPaths[&node]}); 
                outs() << "path graph size = " << pathGraph[&node].size() << "\n";               
                numPaths[&node] += numPaths[Succ];     
                outs() << numPaths[&node];
                validSucc = true;
            }
        }
        if(!validSucc)
        {
            numPaths[&node] = 1;
            outs() << numPaths[&node];
        }
    }
    outs() << "\n";

}

bool revTopSort(block_vector& reverseOrder, block_map& numPaths, block_graph& pathGraph, Loop& loop, BasicBlock& header)
{
    block_set visited;
    revTopSortHelper(reverseOrder, numPaths, pathGraph, visited, loop, header, header); 
    return true;
}

bool InstrumentPass::runOnLoop(llvm::Loop* loop, llvm::LPPassManager& lpm)
{
	// Write your CODE Here
	// I intentionally kept some code here so that you can know some APIs to call
	// Delete them if you find them annoying :)

	// LoopInfo& loopInfo = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
	// DominatorTree& domTree = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
	// DomTreeNode *node = domTree.getNode(loop->getHeader());
	// FunctionType *FunTy = FunctionType::get( Type::getVoidTy( MP->getContext() ), ... );
	// Function *Function = dyn_cast<Function> ( MP->getOrInsertFunction(...) );
	// APInt LoopId(...);
	// Value *init_arg_values[] = { Constant::getIntegerValue(...), ... };
	// CallInst *call = CallInst::Create(...);
	// call->insertBefore(???->getFirstNonPHI());
	// call->insertBefore(latch->getTerminator());
    
    //if( // if inner loop 

    LoopInfo& loopinfo = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
    DominatorTree& domTree = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
    DomTreeNode *node = domTree.getNode(loop->getHeader());
    BasicBlock *header = node->getBlock();
    node = domTree.getNode(loop->getLoopLatch());
    BasicBlock *latch = node->getBlock();
    // DEBUG
    header->printAsOperand(outs(), false);
    latch->printAsOperand(outs(), false); 

    block_vector RTO;
    block_map numPaths;
    block_graph pathGraph;

    // No subloops (i.e. most inner loop)
    if(loop->empty()){
        outs() << "inner loop!\n"; 
         
        // Get Reverse Topological Order
        revTopSort(RTO, numPaths, pathGraph, *loop, *header); 
        outs() << "\n";
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
    }
    else{
        outs() << "outer loop.\n"; 
    }
   
    outs() << "\n";

    for(int i = RTO.size() - 1; i >= 0; i--)
    {
        const BasicBlock* v = RTO[i];
        for(auto wI = pathGraph[v].begin(); wI != pathGraph[v].end(); wI++)
        {
            v->printAsOperand(outs(), false);
            outs() << "->";
            wI->first->printAsOperand(outs(), false);            
            outs() << ": edge value = " << wI->second << "\n";            
        }
    }

    outs() << "\n\n";    

 	// FunctionType *FunTy = FunctionType::get( Type::getVoidTy( MP->getContext() ), ... );
	// Function *Function = dyn_cast<Function> ( MP->getOrInsertFunction(...) );
	// APInt LoopId(...);
	// Value *init_arg_values[] = { Constant::getIntegerValue(...), ... };
	// CallInst *call = CallInst::Create(...);
	// call->insertBefore(???->getFirstNonPHI());
	// call->insertBefore(latch->getTerminator());


    Module *MP = loop->getHeader()->getParent()->getParent();   
    // Set up data 
    ArrayType* ArrayTy_0 = ArrayType::get(IntegerType::get(mod->getContext(), 32), RTO.size());
    PointerType* PointerTy_0 - PointerType::get(ArrayTy_0, 0);

    GlobalVariable* r = new GlobalVariable(MP, 
                                           ArrayTy_0 
                                           false, 
                                           GlobalValue::ExternalLinkage, 
                                           0, 
                                           "r");
    path_profile->setAlignment(16);
    ConstantAggregateZero* const_array_2 = ConstantAggregateZero::get(ArrayTy_0);
    path_profile->setInitializer(const_array_2);

    // Set up functions
    // Init Register
    Function *init = dyn_cast<Function>(MP->getOrInsertFunction("init_path_reg", Type::getVoidTy(MP->getContext()), Type::getInt32Ty(MP->getContext()), NULL));
         
    
    loopinfo.print(outs());
    //int ID = loop->getLoopID()->getMetadataID();
    //loop->getLoopID()->print(outs(), MP,false); 
    APInt loopID(32, 1);
    Value *init_arg_values[] = {Constant::getIntegerValue(Type::getInt32Ty(MP->getContext()), loopID)}; 

    CallInst *call_init = CallInst::Create(init, init_arg_values);
    call_init->insertBefore((RTO[3])->getFirstNonPHI());

    return false;    
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
