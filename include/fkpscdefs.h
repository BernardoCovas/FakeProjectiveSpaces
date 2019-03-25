#ifndef _FKPSCDEFS_H
#define _FKPSCDEFS_H

#include <stdlib.h>
#include <stdio.h>

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256


/*
    Matrix type libfkps should worh with.
*/
typedef float FkpsType_t;

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


typedef struct
{
    int n;
    int currPartition;
    FkpsTriplet_t *triplets;

    int _c;
    int _r;
} FkpsPartition_t;


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
    FkpsPartition_t *stack[BATCHSIZE];
    FkpsPartition_t *partition;
    int n;

    char _fnameprefix[_PART_BCH_STR_LEN];
    int  _stackcounter;
    int  _batchcounter;

    void *_mat; /* Opaque FkpsMat_t */

    FILE *_file;
} FakeProjectiveSpaces_t;


#endif  /* _FKPSCDEFS_H */
