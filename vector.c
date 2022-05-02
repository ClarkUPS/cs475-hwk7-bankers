#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

// TODO - Define vector and matrix operations

/**
 * Adds the recovered resources to vector
 * 
 * @param vector 
 * @param matrix 
 * @param row 
 * @param resourceTypes 
 */
void addToAvailable(int * work, int ** matrix, int row, int resourceTypes){
    for(int a = 0; a < resourceTypes; a++){
        work[a] += matrix[row][a];
    }
}



/**
 * Zeros out the needs of process that have compleated.
 * 
 * @param matrix 
 * @param row 
 * @param resourceTypes 
 */
void zeroOutMatrix(int ** matrix, int row, int resourceTypes){
    for(int a = 0; a < resourceTypes; a++){
        matrix[row][a] = 0;
    }
}



/**
 * Boolean to check if a given process can run to compleation given current resources
 * 
 * @param vector 
 * @param matrix 
 * @param row 
 * @param resourceTypes 
 * @return int: 
 */
int compareVector(int * vector, int ** matrix, int row, int resourceTypes){
    for(int a = 0; a < resourceTypes; a++){
        if(vector[a] < matrix[row][a]){
            return 0; //False
        }
    }
    //printf("Vector row: %d\n", row); REMOVE
    return 1; //True
}



/**
 * @brief To check to see if a process can be compleated
 * 
 * @param finish 
 * @param work 
 * @param available 
 * @param processCount 
 * @param resourceTypes 
 * @return int 
 */
int canFinish(int finish[], int * work, int ** available, int processCount, int resourceTypes){
  for(int a = 0; a < processCount; a++){
      if(finish[a] == 0){
        if(compareVector(work, available, a, resourceTypes)){
          return 1; //There is at least one thread that can finish
        }
     }
  }
  return 0; //No tasks can finish
}



/**
 * matrix1 - matrix = matrix3
 * 
 * @param matrix1 
 * @param matrix2 
 * @param matrix3
 * @param resourceTypes 
 * @param processCount 
 * @return int** 
 */
void subtractTwoMatrices(int ** matrix1, int ** matrix2, int ** matrix3, int resourceTypes, int processCount){
  for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      matrix3[a][b] = (matrix1[a][b] - matrix2[a][b]); //subtraction and saving to matrix3
    }
  }
}



/**
 * @brief Sanity check 2 for if more more is demanded when fully allocated
 * 
 * @param need 
 * @param resourceTypes 
 * @param processCount 
 * @return int 
 */
int checkAllocated(int ** need, int resourceTypes, int processCount){
  for(int a = 0; a < resourceTypes; a++){
    for(int b = 0; b < processCount; b++){
      if(need[a][b] < 0){
        return 0;
      }
    }
  }
  return 1;
}



/**
 * @brief Checks to make sure currenly allocated resources do not exceed total
 * number of resources
 * 
 * @param vector 
 * @param allocated 
 * @param resrouceTypes 
 * @param processCount 
 * @return int 
 */
int checkTotal(int * vector, int ** allocated, int resourceTypes, int processCount){
  int total; //Keep track of current col total
  for(int a = 0; a < resourceTypes; a++){
    total = 0;
    for(int b = 0; b < processCount; b++){
      total += allocated[b][a]; //Sum up collums
    }
    if(total > vector[a]){
      return 0;
    }
  }
  return 1;
}



/**
 * @brief Returns an malloced copy of an entered vector. Needs to copy
 * all infor over as a simple assignment statement won't cut it.
 * 
 * @param available 
 * @param resourceTypes 
 * @return int* 
 */
int * cloneVector(int *available, int resourceTypes){
    int * work = (int *) malloc(sizeof (int) * resourceTypes);

    for(int a = 0; a < resourceTypes; a++){
        work[a] = available[a];
    }
    return work;
}



/**
 * @brief Frees up an entered vector 
 * 
 * @param work 
 */
void freeVector(int * work){
    free(work);
}



/**
 * @brief Frees up an entered matrix
 * 
 * @param matrix 
 * @param processCount 
 * @param resourceTypes 
 */
void freeMatrix(int ** matrix, int processCount){
    for(int a = 0; a < processCount; a++){
            free(matrix[a]);
    }
    free(matrix);
}


void freeAll(int **allocated, int **maximum, int **need, int *vector, int processCount, int *availableResources){
    freeMatrix(allocated, processCount);
    freeMatrix(maximum, processCount);
    freeMatrix(need, processCount);
    freeVector(vector);
    freeVector(availableResources);
}



/**
 * @brief Converts total resources to available resources
 * 
 * @param allocated 
 * @param vector 
 * @param resourceTypes 
 * @param processCount 
 * @return int* 
 */
int * available(int ** allocated, int * vector, int resourceTypes, int processCount){
  for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      vector[b] -= allocated[a][b];
    }
  }
  return vector;
}



/**
 * @brief Set the Finish vector to inital unfinished state:
 * 
 * @param finish 
 * @param processCount 
 */
void setFinish(int finish[], int processCount){
    for(int a = 0; a < processCount; a++){
        finish[a] = 0;
    }
} 



/**
 * @brief Checks to see if all process are complete
 * 
 * @param finished 
 * @param processCount 
 * @return int 
 */
int unfinished(int finished[], int processCount){
    for(int a = 0; a < processCount; a++){
        if(finished[a] == 0){
            return 0; //There must be at least one unfinished process
        }
    }
    return 1; //All process are complete
}



/**
 * Prints all the working matrixies and vectors:
 * 
 * @param processCount 
 * @param resourceTypes 
 * @param allocated 
 * @param maximum 
 * @param need 
 * @param vector 
 */
void printall(int processCount, int resourceTypes, int ** allocated, int ** maximum, int ** need, int * vector){

printf("=======\nVector:\n");
for(int a = 0; a < resourceTypes; a++){
    printf("%d ", vector[a]);
}

printf("\n\nMaximum:\n");
  for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      printf("%d ", maximum[a][b]);
    }
    printf("\n");
  }


printf("\nAllocated:\n");
for(int a = 0; a < processCount; a++){
    for(int b = 0; b < resourceTypes; b++){
      printf("%d ", allocated[a][b]);
    }
    printf("\n");
  }
  printf("\n");
  //Not needed in the final version
// printf("\nNeed:\n");
//   for(int a = 0; a < processCount; a++){
//     for(int b = 0; b < resourceTypes; b++){
//       printf("%d ", need[a][b]);
//     }
//     printf("\n");
//   }
//   printf("=======\n");
}