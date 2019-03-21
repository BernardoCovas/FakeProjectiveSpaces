#ifndef _FKPS_H
#define _FKPS_H

#include <stdbool.h>
#include <stdio.h>

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256

/*
    FakeProjectiveSpaces_t base data structure.
    
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

    void *_mat; /* FkpsMat_t *_mat */

    FILE *_file;
} FakeProjectiveSpaces_t;

/* 
    Alocates an instance of PartitionBatchInit.
    'filename' is the result output.
    Returns NULL if malloc() fails.
*/
FakeProjectiveSpaces_t *FakeProjectiveSpacesInit(int n, char *filename);

/* FakeProjectiveSpacesDeInit
    Releases `FakeProjectiveSpacesInit`'s resources.
*/
void FakeProjectiveSpacesDeInit(FakeProjectiveSpaces_t *projectiveSpaces);

/*
    Appends the vector `v` to the stack,
    ocationally flushing it to the file
    if it's `_base_pointer` is at `BATCH_SIZE`
    or if `flush` is true.
*/
void FakeProjectiveSpacesDump(FakeProjectiveSpaces_t *projectiveSpaces, long *v, bool flush);

/*
    Flushes thr cotents to `_file`.
*/
void FakeProjectiveSpacesFlush(FakeProjectiveSpaces_t *projectiveSpaces);

/*
    Returns the determinant of the internal matrix `_mat`, after applying the parameters `v`.
*/
long FakeProjectiveSpacesDeterminantQ(FakeProjectiveSpaces_t *projectiveSpaces, long *v);

/*
    Well, I suppose it partitions the thing
    after a few million loops.
*/
void FakeProjectiveSpacesPartition(FakeProjectiveSpaces_t *projectiveSpaces, int toPart, int numWorkers);


#endif /* _FKPS_H */