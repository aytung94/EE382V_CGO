#include "epp_runtime.h"
#include <iostream>
#include <vector>
#include <unordered_map> 

using namespace std;

unordered_map<int, unordered_map<int, int>> path_profile;
unordered_map<int, int> r;

extern "C" void init_path_reg(int loopId){   
//    cout << loopId << "init paths" << "! ";
//    cout << "initializing path for loop: " << loopId << "\n";
    
    if(path_profile.find(loopId) == path_profile.end())
    {
        path_profile.insert({loopId, unordered_map<int,int>()});   
    }
    if(r.find(loopId) == r.end()){
        r.insert({loopId, 0});
    }
    else{
        r[loopId] = 0;
    }
}
extern "C" void inc_path_reg(int loopId, int val){
//  cout << loopId << "increment me by " << val <<  "! ";/
//  cout << "incrementing path by " << val << " for loop: " << loopId << "\n";

    r[loopId] += val;
}

extern "C" void finalize_path_reg(int loopId){
//    cout << loopId << "finalize me!\n";
//    cout << "finalizing path for loop: " << loopId << "\n";

    if(path_profile[loopId].find(r[loopId]) == path_profile[loopId].end()){
        path_profile[loopId].insert({r[loopId], 1});
    }
    else{
        path_profile[loopId][r[loopId]]++;
    }
}

extern "C" void dump_path_regs(){
//    printf("\nLoopID: PathID: Value:\n");

    for(auto itP = path_profile.begin(); itP != path_profile.end(); itP++){
        int indP = 0;
        for(auto itR = itP->second.begin(); itR != itP->second.end(); itR++){
//            cout << "Loop # " << itP->first  <<  " Path #" << itR->first << " Count #" << itR->second << "\n";
//              cout << "(" << itR->first << ")";
           printf("%-6d  %-6d  %-6d\n", itP->first, indP, itR->second);            
           indP++;
        }
    }    
}


