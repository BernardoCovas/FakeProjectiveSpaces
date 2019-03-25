#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <random>

#include "fkps.h"
#include "fkpspartition.h"

#include "fkpsdefinitions.hh"

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256


void __log_err_malloc(void);
void __log_err_fopen(const char *fname);
void __log_dbg_flush(int batch);


FakeProjectiveSpaces_t *FakeProjectiveSpacesInit(

    int n,
    const char *filename

)
{
    FILE *f = fopen(filename, "w");
    if (f ==  NULL) { __log_err_fopen(filename);  return NULL; }

    FakeProjectiveSpaces_t *projectiveSpaces;


    projectiveSpaces = (FakeProjectiveSpaces_t *) malloc(sizeof(FakeProjectiveSpaces_t));
    if (projectiveSpaces == NULL) { fclose(f); __log_err_malloc(); return NULL; };

        projectiveSpaces->n = n;
        projectiveSpaces->_batchcounter = 0;
        projectiveSpaces->_stackcounter = 0;
        projectiveSpaces->_file = f;
        projectiveSpaces->_mat = (void *) new FkpsMat_t;

    FkpsPartition_t *partition = projectiveSpaces->partition;
        partition = FkpsPartitionInit(n);
        if (partition == NULL) { fclose(f); __log_err_malloc(); return NULL; };

    char *fname = projectiveSpaces->_fnameprefix;
    strncpy(fname, filename, _PART_BCH_STR_LEN);
    fname[_PART_BCH_STR_LEN - 1] = '\0'; // Allways null-terminate

    return projectiveSpaces;
}


void FakeProjectiveSpacesDeInit(

    FakeProjectiveSpaces_t *fakeProjectiveSpaces

)
{

    for (int i=0; i<BATCHSIZE; i++)
        free(&fakeProjectiveSpaces->stack[i]);

    delete (FkpsMat_t *) fakeProjectiveSpaces->_mat;
    fclose(fakeProjectiveSpaces->_file);

    FkpsPartitionDeInit(fakeProjectiveSpaces->partition);
    free(fakeProjectiveSpaces);
}


void FakeProjectiveSpacesMatLoadRandom(

    FakeProjectiveSpaces_t *fakeProjectiveSpaces

)
{
    // TODO (bcovas) rand int remove
    int r = 20, c = 20;
    int m = 20;

    FkpsMat_t *mat = (FkpsMat_t *) fakeProjectiveSpaces->_mat;
        mat->resize(r, c);
        mat->setRandom();

    FkpsPartitionRandomAssign(fakeProjectiveSpaces->partition, r, c, m);
}


bool FakeProjectiveSpacesAssignTriplet(

    FakeProjectiveSpaces_t *fakeProjectiveSpaces,
    FkpsTriplet_t *t

)
{
    FkpsMat_t *mat = (FkpsMat_t *) fakeProjectiveSpaces->_mat;
    (*mat)(t->r, t->c) = t->val;

    return true;
}


bool FakeProjectiveSpacesAssignTriplets(

    FakeProjectiveSpaces_t *fakeProjectiveSpaces,
    FkpsTriplet_t *triplets,
    int n

)
{
    FkpsMat_t *mat = (FkpsMat_t *) fakeProjectiveSpaces->_mat;
    FkpsType_t _n = fakeProjectiveSpaces->n;

    // TODO (bcovas): Temporary
    assert(_n >= n);

    if (n > _n)
        return false;

    for (int i=0; i<n; i++)
    {
        FkpsTriplet_t *d = &triplets[i];
        (*mat)(d->r, d->c) = d->val;
    }

    return true;
}


void FakeProjectiveSpacesDump(

    FakeProjectiveSpaces_t *fakeProjectiveSpaces,
    bool forceFlush

)
{
    int  *_sc = &(fakeProjectiveSpaces->_stackcounter);
    fakeProjectiveSpaces->stack[*_sc] = FkpsPartitionCopy(fakeProjectiveSpaces->partition);

    if (++(*_sc) < BATCHSIZE && !forceFlush)
        return;
    
    FakeProjectiveSpacesFlush(fakeProjectiveSpaces);
}


void FakeProjectiveSpacesFlush(

    FakeProjectiveSpaces_t *projectiveSpaces

)
{
    FILE *f   = projectiveSpaces->_file;
    int  *_sc = &(projectiveSpaces->_stackcounter);
    int  *_bc = &(projectiveSpaces->_batchcounter);
    int  n    = projectiveSpaces->n;

    __log_dbg_flush(*_bc);

    for (int i = 0; i < *_sc; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(f, j==(n-1) ?"%d\n":"%d,", (int) projectiveSpaces->stack[i]->triplets[j].val);

    (*_bc)++;
    (*_sc) = 0;
}


FkpsType_t FakeProjectiveSpacesDeterminantQ(

    FakeProjectiveSpaces_t *projectiveSpaces

)
{
    FkpsMat_t *mat = (FkpsMat_t *) projectiveSpaces->_mat;
    return (mat->determinant());
}


void FakeProjectiveSpacesSolvePartial(

    FakeProjectiveSpaces_t *projectiveSpaces,
    FkpsType_t toPart

)
{
    int n = projectiveSpaces->n;
    FkpsType_t *v = (FkpsType_t *) malloc(sizeof(FkpsType_t) * n); // On stack, only const array sizes.
    
    for (int j = 0; j < n; ++j) {
        v[j] = 1;
    }
    
    // TODO: N Partition.
    while(1)
    {
        FkpsPartitionIncrement(projectiveSpaces->partition);
        FakeProjectiveSpacesDeterminantQ(projectiveSpaces);
    }

    /* 
    
    FkpsType_t cap = toPart - n + 1;
    FkpsType_t i, s;
    
    v[0] = cap;
    while (v[n-1] != cap)
    {
        i = n;
        while (v[--i] == 1);

        if (i != n-1)
        { 
            --v[i]; v[i+1] = 2;
        } 
        else
        {
            while (v[--i] == 1);
            --v[i]; s = v[n-1]; v[n-1] = 1; v[i+1] = s+1;
        }

        FakeProjectiveSpacesDeterminantQ(projectiveSpaces, v);
    }

    */

    FakeProjectiveSpacesFlush(projectiveSpaces);
    free(v);
}


void __log_err_malloc()
{
    printf("ERR: Could not allocate enough resources.\n");
}

void __log_err_fopen(const char *fname)
{
    printf("ERR: Could not open: %s.\n", fname);
}

void __log_dbg_flush(int batch)
{
    printf("DBG: Flushing batch: %d.\n", batch);
}