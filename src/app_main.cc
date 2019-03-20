#include <stdlib.h>
#include <stdio.h>

#include "partitionsbatch.h"

int main(int argc, char* args[]) {
    
    if (argc != 4) {
        printf("Wrong number of arguments\n");
        return 0;
    }

    int toPart  = atoi(args[1]);
    int n       = atoi(args[2]);
    char *fname = args[3];
    
    printf("Going to partition %d into %d\n", toPart, n);

    PartitionBatch_t *partitionBatch = PartitionBatchInit(n, fname);
    if (partitionBatch == NULL) { printf("Could not initialize."); return -1; }

    PartitionBatchPartition(partitionBatch, toPart, 1);
    return 0;
}