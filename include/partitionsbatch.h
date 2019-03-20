#ifndef _PARTITIONSBATCH_H
#define _PARTITIONSBATCH_H

#include <stdbool.h>
#include <stdio.h>


#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256

/*
    PartitionBatch_t base data structure.
    
    'stack' will hold several possible partitions until it
    is forced to flush them to '_file'.

    '_stackcounter' holds the number of partitions already stored 
    but not flushed.

    '_batchcounter' holds the number of batches already dumped.
*/
typedef struct
{
    long *stack[BATCHSIZE];
    int n;
    
    char _fnameprefix[_PART_BCH_STR_LEN];
    int _stackcounter;
    int _batchcounter;

    FILE *_file;
} PartitionBatch_t;

/* 
    Alocates an instance of PartitionBatchInit.
    Returns NULL if malloc() fails.
*/
PartitionBatch_t *PartitionBatchInit(int n, char *filename);

/* 
    Releases PartitionBatchInit's resources.
*/
void PartitionBatchDeinit(PartitionBatch_t *partitionBatch);

/*
    Appends the vector v to the stack,
    ocationally flushing it to the file
    if it's bp is at BATCH_SIZE or if
    'flush' is true.
*/
void PartitionBatchDump(PartitionBatch_t *partitionBatch, long *v, bool flush);

/*
    Flushes thr cotents to _file.
*/
void PartitionBatchFlush(PartitionBatch_t *partitionBatch);

/*
    Calculates the condition. Case met,
    dumps to the stack using 'PartitionBatchDump()'.
*/
void PartitionBatchDeterminantQ(PartitionBatch_t *partitionBatch, long *v);

/*
    Well, I suppose it partitions the thing
    after a few million loops.
*/
void PartitionBatchPartition(PartitionBatch_t *partitionBatch, int toPart, int numWorkers);


#endif /* _PARTITIONSBATCH_H */