#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vector.h"
#include "banker.h"

int **allocated; //inintal allocated read form txt file
int **maximum; //inital maximum read from txt file
int **need; //need calculated from max - allocated

int *vector; //Total resrouces / avalable resources

int resourceTypes;
int processCount;

int next;


int main(int argc, char *argv[])
{
  // TODO: attempt to open scenario file and scan data into allocated structures
  
  //Ensure correct number of args
  if(argc < 2 || argc > 2){
    printf("Usage: ./bankers <scenerio file>\n");
    return 0;
  }

  char* file = argv[1];
  //strcat(file,".txt");

  printf("file name input: %s\n",file); //REMOVE
  FILE *text; //Stores conetence of text file

   text = fopen(file,"r");

   if(text == NULL){
     printf("text file %s does not exist\n",file);
     fclose(text);
     return 0;
   }
  
  //Get number of resouces/processes
  fscanf(text, "%d", &resourceTypes); //get/set resources types
  fscanf(text, "%d", &processCount); //get/set  process Count
  printf("Rty: %d Pcnt: %d\n", resourceTypes,processCount);

  //Malloc for process allocated
  allocated = (int **) malloc(sizeof (int *) *processCount);
  for(int a = 0; a < processCount; a++){
    allocated[a] = (int *) malloc(sizeof (int) *resourceTypes);
  }

  //Malloc for maximum
  maximum = (int **) malloc(sizeof (int *) *processCount);
  for(int a = 0; a < processCount; a++){
    maximum[a] = (int *) malloc(sizeof (int) *resourceTypes);
  }

  //Malloc for need matrix
  need = (int **) malloc(sizeof (int *) *processCount);
  for(int a = 0; a < processCount; a++){
    need[a] = (int *) malloc(sizeof (int) *resourceTypes);
  }

  //Malloc for vector
  vector = (int *) malloc(sizeof (int) * resourceTypes);
  
  //Get and set vector inital contence
  for(int a = 0; a < resourceTypes; a++){
    fscanf(text, "%d", &vector[a]);
  }

  
  //Set matrix variables by reading from file
  for (int i = 0; i < 2; i++){
    for(int a = 0; a < processCount; a++){
      for(int b = 0; b < resourceTypes; b++){
        if(i < 1){
          fscanf(text, "%d", &maximum[a][b]);
        }else{
          fscanf(text, "%d", &allocated[a][b]);
        }
      }
    }
  }
  
  printall(processCount, resourceTypes, allocated, maximum, need, vector);
 
  //Calculate and populate need matrix:
  subtractTwoMatrices(maximum, allocated, need, resourceTypes, processCount);
  
    //Sanity Checks
  //Sanity check 1:
  if(!checkTotal(vector, allocated, resourceTypes, processCount)){
    printf("Integrity test failed: allocated resources exceed total resources: SC 1\n");

    freeAll(allocated, maximum, need, vector, processCount);

    return 0;

    //Sanity check 2
  }else if(!checkAllocated(need, resourceTypes,  processCount)){
    printf("Integrity test failed: allocated resources exceed demand for Threads: SC 2\n");
    
    freeAll(allocated, maximum, need, vector, processCount);

    return 0;
  }

  //Convert total resrouces to avalable resrouces
  vector = available(allocated, vector, resourceTypes, processCount);

   // TODO: Run banker's safety algorithm
  //int finish[] = {1,1,1,1,1};
  //printf("Can finish test: %d\n", canFinish(finish, vector, need, processCount, resourceTypes));
  
  isSafe(vector, allocated, need, resourceTypes, processCount);

  //printall(processCount, resourceTypes, allocated, maximum, need, vector);
  
  freeAll(allocated, maximum, need, vector, processCount); //Make sure to free up all resources before ending
  
  fclose(text);
  return 0;
}

