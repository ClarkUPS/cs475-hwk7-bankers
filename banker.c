#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here

int isSafe(int * available, int ** alloc, int **need, int resourceTypes, int processCount){

    int * work = cloneVector(available, resourceTypes);
    int finish[processCount]; 
    
    int processOrder[processCount];
    int processOrderCount = 0;

    setFinish(finish, processCount);

    printf("Processes run order:\n");
    while(!unfinished(finish,processCount) && canFinish(finish, work, need, processCount, resourceTypes)){
        
        for(int a = 0; a < processCount; a++){
            //Make sure process has not already run
            if(finish[a] == 0){
                //If process can un
                if(compareVector(work, need, a, resourceTypes)){
                   
                    addToAvailable(work, alloc, a, resourceTypes);
                    processOrder[processOrderCount] = a;
                    processOrderCount++;
                    finish[a] = 1;
                    for(int b = 0; b < resourceTypes; b++){
                        //printf("%d ", work[b]);
                    }
                    break; //break out of for Loop
                }
            }
        //do again if equal one/cannot run
        }
        
    }
    
    //Process pretends to run

free(work); //Make sure to free back up the cloned work vector

if(unfinished(finish,processCount)){
    printf("Safe: ");

    for(int a = 0; a < processCount; a++){
        printf("T%d ", processOrder[a]);
    }
    
printf("\n");

    return 0;
}else{
    printf("UNSAFE: ");
    for(int a = 0; a < processCount; a++){
        if(finish[a] == 0){
            printf("T%d ", a);
        }
    }
    printf(" cannot finish\n");
    return 0;
 }
}







