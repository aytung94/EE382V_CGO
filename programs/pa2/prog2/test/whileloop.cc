#include <stdio.h>
#include <stdlib.h>
#include "epp_runtime.h"

int
main(int argc, char **argv) {
   
  int max = atoi(argv[1]);
  int i = 0;
  while(i < max)
  {
    if(0 == i % 2){
      printf("even\n");      
    }
    else{
      printf("odd\n");
    }
    i++;
  }

  dump_path_regs();
  return 0;
}
