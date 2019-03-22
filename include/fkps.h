#ifndef _FKPS_H
#define _FKPS_H

#include <stdbool.h>
#include <stdio.h>

#include "fkpscdefs.h"

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256

/*
    FkpsTriplet_t base data structure.
    Represents one variable in the matrix.
*/
typedef struct
{
    int r;
    int c;
    FkpsType_t val;
} FkpsTriplet_t;

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
    FkpsType_t *stack[BATCHSIZE];
    FkpsTriplet_t *triplets;
    int n;

    char _fnameprefix[_PART_BCH_STR_LEN];
    int  _stackcounter;
    int  _batchcounter;

    void *_mat; /* FkpsMat_t */

    FILE *_file;
} FakeProjectiveSpaces_t;

/*
    Alocates an instance of PartitionBatchInit.
    'filename' is the result output.
    Returns NULL if malloc() fails.
*/
FakeProjectiveSpaces_t *FakeProjectiveSpacesInit(
    int n,
    const char *filename
    );

/* FakeProjectiveSpacesDeInit
    Releases `FakeProjectiveSpacesInit`'s resources.
*/
void FakeProjectiveSpacesDeInit(
    FakeProjectiveSpaces_t *projectiveSpaces
    );

/**
 * Sets the internal `Eigen::Matrix` to
 * a random (20, 20) matrix.
*/
void FakeProjectiveSpacesMatLoadRandom(
    FakeProjectiveSpaces_t *fakeProjectiveSpaces
    );

/**
 * Assigns `triplet` to the internal matrix.
 */
bool FakeProjectiveSpacesAssignTriplets(
    FakeProjectiveSpaces_t *fakeProjectiveSpaces,
    FkpsTriplet_t *triplet
    );

/**
 * Assigns `n` items from`triplets`
 * to the internal matrix.
 * Returns `false` if any error occurs.
 * If `false` is returned, no assignment
 * was done.
 */
bool FakeProjectiveSpacesAssignTriplets(
    FakeProjectiveSpaces_t *fakeProjectiveSpaces,
    FkpsTriplet_t *triplets,
    int n
    );

/**
 * Appends the vector `v` to the stack,
 * ocationally flushing it to the file
 * if it's `_base_pointer` is at `BATCH_SIZE`
 * or if `flush` is true.
*/
void FakeProjectiveSpacesDump(
    FakeProjectiveSpaces_t *projectiveSpaces,
    FkpsType_t *v,
    bool flush);

/**
 * Flushes the  cotents to `_file`.
*/
void FakeProjectiveSpacesFlush(
    FakeProjectiveSpaces_t 
    *projectiveSpaces
    );

/**
 * Returns the determinant of the internal
 * `Eigen::Matrix`.
*/
FkpsType_t FakeProjectiveSpacesDeterminantQ(
    FakeProjectiveSpaces_t *projectiveSpaces
    );

/*
    Well, I suppose it partitions the thing
    after a few million loops.
*/
void FakeProjectiveSpacesPartition(
    FakeProjectiveSpaces_t *projectiveSpaces,
    FkpsType_t toPart
    );


#endif /* _FKPS_H */