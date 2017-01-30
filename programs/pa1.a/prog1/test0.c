#include <stdio.h>

#define SIZE 20

int a[10];
int b[SIZE];

int factor(int n) {
  int i, ret = 1;
  for (i = 1; i <= n; i++)
    ret *= i;
  return ret;
}

int main() {
  int i;
  for (i = 0; i < 10; i++) {
    if (i == 0)
      a[i] = 1;
    else 
      a[i] = factor(i);
  }
    
  int ind = 1;
  ind = 0;
  int sum = 0;
  while(ind != SIZE){
    sum += b[ind];
    ind++;
  }

  printf("factor[9]= %d\n", a[9]);
  printf("sum = %d\n", sum);
  return 0;
}
