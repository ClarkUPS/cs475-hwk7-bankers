#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "vector.h"
#include "banker.h"

int **allocated;
int **maximum;
int *vector;

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

  //Malloc for vector
  vector = (int *) malloc(sizeof (int) * resourceTypes);
  
  //Get and set vector inital contence
  for(int a = 0; a < resourceTypes; a++){
    fscanf(text, "%d", &vector[a]);
  }

  
  //Set matrix variables
  for (int i = 0; i < 2; i++)
  {
    for(int a = 0; a < processCount; a++){
      for(int b = 0; b < resourceTypes; b++){
        if(i < 1){
          fscanf(text, "%d", &allocated[a][b]);
        }else{
          fscanf(text, "%d", &maximum[a][b]);
        }
      }
    }
  }
  
  printall(processCount, resourceTypes, allocated, maximum, vector);
    

  
  
  // srand(time(NULL));
  // for(int a = 0; a < resourceTypes; a++){
  //   vector[a] = rand() % 100;
  // }

  


//REMOVE Tester
  
  // for(int a = 0; a < processCount; a++){
  //   for(int b = 0; b < resourceTypes; b++){
  //     allocated[a][b] = rand() % 100;
  //   }
  // }


  // for(int a = 0; a < processCount; a++){
  //   for(int b = 0; b < resourceTypes; b++){
  //     printf("%d ", allocated[a][b]);
  //   }
  //   printf("\n");
  // }

// for(int a = 0; a < processCount; a++){
//     for(int b = 0; b < resourceTypes; b++){

//     }
//   }

  
  

  // do{
  //   fscanf(text, "%d", &next);
  //   printf("Next: %d,\n", next);
  // }while(next != NULL);



  fclose(text);


  // TODO: Run banker's safety algorithm

  return 0;
}

