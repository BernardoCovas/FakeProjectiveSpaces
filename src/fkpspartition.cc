#include <Eigen/Dense>

#include "fkpsdefinitions.hh"
#include "fkpspartition.h"

FkpsPartition_t * FkpsPartitionInit(
    int n
)
{
    FkpsPartition_t *tripletPartition = (FkpsPartition_t *) malloc(sizeof(FkpsPartition_t));
    tripletPartition->triplets = (FkpsTriplet_t *) calloc(n, sizeof(FkpsTriplet_t));

    tripletPartition-> n = n;
    tripletPartition->_c = 0;
    tripletPartition->_r = 0;

    // TODO:
    return tripletPartition;
}

void FkpsPartitionDeInit(

    FkpsPartition_t *partition

)
{
    free(partition->triplets);
    free(partition);
}

void FkpsPartitionRandomAssign(
    
    FkpsPartition_t *partition,
    int r,
    int c,
    int maxVal

)
{

    FkpsTriplet_t *triplets = partition->triplets;

    for (int i=0; i<partition->n; i++)
    {
        triplets[i].r   = std::rand() / RAND_MAX * r;
        triplets[i].c   = std::rand() / RAND_MAX * c;
        triplets[i].val = std::rand() / RAND_MAX * maxVal;
    }

}


FkpsPartition_t *FkpsPartitionCopy(
    FkpsPartition_t *partition
)
{
    int n = partition->n;

    FkpsPartition_t *newPrtn = FkpsPartitionInit(n);
    FkpsTriplet_t *triplets = newPrtn->triplets;

    memcpy(newPrtn, partition, sizeof(FkpsPartition_t));
    memcpy(triplets, partition->triplets, sizeof(FkpsTriplet_t) * n);

    newPrtn->triplets = triplets;

    return newPrtn;
}

// TODO (bcovas)
void FkpsPartitionIncrement(

    FkpsPartition_t *fkpsPartition

)
{
    int *cp = &(fkpsPartition->currPartition);
    int n  = fkpsPartition->n;
    
    assert(n > 0); // TODO: (bcovas) Change
    
    FkpsTriplet_t *tplts = fkpsPartition->triplets;

    int swp = (*cp) % n; 
    // [4, 2, 1, 1]

    (*cp)++;
}