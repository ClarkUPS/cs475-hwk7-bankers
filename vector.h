
// TODO: function prototypes of vector and matrix operations

void addToAvailable(int * vector, int ** matrix, int row, int resourceTypes);

void zeroOutMatrix(int ** matrix, int row, int resourceTypes);

int compareVector(int * vector, int ** matrix, int row, int resourceTypes);

int canFinish(int finish[], int * work, int ** available, int processCount, int resourceTypes);

void subtractTwoMatrices(int ** matrix1, int ** matrix2, int ** matrix3, int resourceTypes, int processCount);

int checkAllocated(int ** need, int resourceTypes, int processCount);

int checkTotal(int * vector, int ** allocated, int resourceTypes, int processCount);

int * cloneVector(int *available, int resourceTypes);

void freeVector(int * work);

void freeMatrix(int ** matrix, int processCount);

void freeAll(int **allocated, int **maximum, int **need, int *vector, int processCount);

int * available(int ** allocated, int * vector, int resourceTypes, int processCount);

void printall(int processCount, int resourceTypes, int ** allocated, int ** maximum, int ** need, int * vector);
