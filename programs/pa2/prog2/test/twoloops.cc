#include <stdio.h>
#include <stdlib.h>
#include "epp_runtime.h"

int
main(int argc, char **argv) {
  for (int i = 0, e = atoi(argv[1]); i < e; ++i) {
    if ((i + argc) % 3) {
      printf("Truey\n");
      if(i < 7)
      {
        printf("I am %d\n", i);
      }
    } else {
      printf("Falsey\n");
    }
  }
  
 for (int j = 0; j < 10; j++){
    if(j ==2)
        printf("at 10");
    else if(j == j % 3)
        printf("div 3");
    else{
        
        printf("dlksd");
    }
    printf("\n\n%d\n\n", j);
 }

 dump_path_regs();
  return 0;
}
