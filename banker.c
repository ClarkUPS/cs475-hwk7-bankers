#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

int isSafe(int * available, int ** alloc, int **need, int resourceTypes, int processCount){

    int * work = cloneVector(available, resourceTypes);
    int finish[processCount]; 
    setFinish(finish, processCount);


        printf("Inital Work: ");
        for(int b = 0; b < resourceTypes; b++){
        printf("%d ", work[b]);
        }

    printf("Processes run order:\n");
    while(!unfinished(finish,processCount) && canFinish(finish, work, need, processCount, resourceTypes)){
        
        for(int a = 0; a < processCount; a++){
            //Make sure process has not already run
            if(finish[a] == 0){
                //If process can un
                if(compareVector(work, need, a, resourceTypes)){
                   
                    addToAvailable(work, alloc, a, resourceTypes);
                    finish[a] = 1;

                    printf("new Work: ");
                    for(int b = 0; b < resourceTypes; b++){
                        printf("%d ", work[b]);
                    }
                    printf(" process: %d\n", a);

                    break; //break out of for Loop
                }
            }
            //do again if equal one/cannot run
        }
        
    }
    
    //Process pretends to run
    printf("new Work");
    for(int a = 0; a < resourceTypes; a++){
        printf("%d ", work[a]);
    }


if(unfinished(finish,processCount)){
    printf("Safe!\n");
    return 1;
}else{
    printf("Not safe!\n");
    return 0;
}
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



