#include <stdio.h>
#include <stdlib.h>
#include "epp_runtime.h"

int
main(int argc, char **argv) {
   
  for (int i = 0, e = atoi(argv[1]); i < e; ++i) {
    if ((i + argc) % 3) {
      if(i == 0){
        i++;
        i--;
      }      
      if(i == 1){
        i--;
        i++;
      }
    } else {
      if(i == 0){
        i--;
        i++;
      }
      else if(i == 1){
        i++;
        if(i == 8){
          i--;
        }
        else{
          i--;
        }
      }
      else{
        i--;
        if(i < 5){
            i++;
        }
        else if(i >5){
            i++;
        }
        else if( i == 5){
            i++;
        }
      }
    }
  }
  
  dump_path_regs();
  return 0;
}
