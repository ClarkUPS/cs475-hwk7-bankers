#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations




//Simple print all for testing
void printall(int processCount, int resourceTypes, int ** allocated, int ** maximum, int * vector){

printf("=======\nVector:\n");

for(int a = 0; a < resourceTypes; a++){
    printf("%d ", vector[a]);
}

printf("\n\nAllocated:\n");

for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      printf("%d ", allocated[a][b]);
    }
    printf("\n");
  }


printf("\nMaximum:\n");
  for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      printf("%d ", maximum[a][b]);
    }
    printf("\n");
  }

  printf("=======\n");
}