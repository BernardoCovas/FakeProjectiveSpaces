#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "detfuncparsed.h"
#include "partitionsbatch.h"

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256


void __log_err_malloc(void);
void __log_err_fopen(char *fname);
void __log_dbg_flush(int batch);


PartitionBatch_t *PartitionBatchInit(int n, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) { __log_err_fopen(filename);  return NULL; }
    
    PartitionBatch_t *partitionBatch;
    
    partitionBatch = (PartitionBatch_t *) malloc(sizeof(PartitionBatch_t));
    if (partitionBatch == NULL) { fclose(f); __log_err_malloc(); return NULL; };
    
    partitionBatch->n = n;
    partitionBatch->_batchcounter = 0;
    partitionBatch->_stackcounter = 0;
    partitionBatch->_file = f;

    char *fname = partitionBatch->_fnameprefix;
    strncpy(fname, filename, _PART_BCH_STR_LEN);
    fname[_PART_BCH_STR_LEN - 1] = '\0'; // Allways null-terminate

    for (int i=0; i<BATCHSIZE; i++)
    {
        partitionBatch->stack[i] = (long *) malloc(sizeof(long) * n);
        if (partitionBatch->stack[i] == NULL)
        {
            PartitionBatchDeinit(partitionBatch);
            __log_err_malloc();
            return NULL;
        }
    }

    return partitionBatch;
}


void PartitionBatchDeinit(PartitionBatch_t *partitionBatch)
{
    for (int i=0; i<BATCHSIZE; i++)
        free(partitionBatch->stack[i]);

    fclose(partitionBatch->_file);
    free(partitionBatch);
}


void PartitionBatchDump(PartitionBatch_t *partitionBatch, long *v, bool flush)
{
    FILE *f   = partitionBatch->_file;
    char *_fp = partitionBatch->_fnameprefix;
    int  *_sc = &(partitionBatch->_stackcounter);
    int  *_bc = &(partitionBatch->_batchcounter);
    int  n    = partitionBatch->n;

    memcpy(partitionBatch->stack[*_sc], v, sizeof(long) * n);

    if (++(*_sc) < BATCHSIZE && !flush)
        return;

    __log_dbg_flush(*_bc);

    for (int i = 0; i < *_sc; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(f, j==(n-1) ?"%ld\n":"%ld,", partitionBatch->stack[i][j]);

    (*_bc)++;
    (*_sc) = 0;
}


void PartitionBatchDeterminantQ(PartitionBatch_t *partitionBatch, long *v)
{
    if (DET_FUNC_PARSED_00(v) == 0)
        PartitionBatchDump(partitionBatch, v, false);
}


void PartitionBatchPartition(PartitionBatch_t *partitionBatch, short toPart, int numWorkers) {

    int n = partitionBatch->n;
    long *v = (long *) malloc(sizeof(long) * n); // On stack, only const array sizes.
    
    for (int j = 0; j < n; ++j) {
        v[j] = 1;
    }
    
    long cap = toPart - n + 1;
    long i, s;
    
    v[0] = cap;

    PartitionBatchDeterminantQ(partitionBatch, v);
    
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

        PartitionBatchDeterminantQ(partitionBatch, v);
    }

    free(v);
}


void __log_err_malloc()
{
    printf("ERR: Could not allocate enough resources.\n");
}

void __log_err_fopen(char *fname)
{
    printf("ERR: Could not open: %s.\n", fname);
}

void __log_dbg_flush(int batch)
{
    printf("DBG: Flushing batch: %d.\n", batch);
}