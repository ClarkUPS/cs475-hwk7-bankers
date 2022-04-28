/* declarations related to banker's algorithm */
int isSafe(int * available, int ** alloc, int **need, int resourceTypes, int processCount);

void setFinish(int finish[], int processCount);

int unfinished(int finished[], int processCount);