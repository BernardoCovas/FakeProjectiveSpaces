#ifndef _FKPSPARTITION_H
#define _FKPSPARTITION_H

#include "fkpscdefs.h"


/**
 *  Allocates a `FkpsTripletPartition_t` data structure
 *  associated with one `FakeProjectiveSpaces_t`.
 */
FkpsPartition_t *FkpsPartitionInit(
    int n
);


/**
 * 
 */
void FkpsPartitionDeInit(
    FkpsPartition_t *fkpsPartition
);


/**
 * 
 */
void FkpsPartitionRandomAssign(
    FkpsPartition_t *fkpsPartition,
    int r,
    int c,
    int maxVal
);


/**
 * 
 */
FkpsPartition_t *FkpsPartitionCopy(
    FkpsPartition_t *fkpsPartition
);


/**
 * Increments the permutation by one.
 */
void FkpsPartitionIncrement(
    FkpsPartition_t *fkpsPartition
);



#endif /* _FKPSPARTITION_H */
