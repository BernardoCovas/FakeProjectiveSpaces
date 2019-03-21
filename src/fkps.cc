#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "detfuncparsed.h"
#include "fkps.h"

#define BATCHSIZE 1000000
#define _PART_BCH_STR_LEN 256


void __log_err_malloc(void);
void __log_err_fopen(char *fname);
void __log_dbg_flush(int batch);


FakeProjectiveSpaces_t *FakeProjectiveSpacesInit(int n, char *filename)
{
    FILE *f;
    if (fopen_s(&f, filename, "w") != 0) { __log_err_fopen(filename);  return NULL; }

    FakeProjectiveSpaces_t *projectiveSpaces;
    
    projectiveSpaces = (FakeProjectiveSpaces_t *) malloc(sizeof(FakeProjectiveSpaces_t));
    if (projectiveSpaces == NULL) { fclose(f); __log_err_malloc(); return NULL; };
    
    projectiveSpaces->n = n;
    projectiveSpaces->_batchcounter = 0;
    projectiveSpaces->_stackcounter = 0;
    projectiveSpaces->_file = f;

    char *fname = projectiveSpaces->_fnameprefix;
    strcpy_s(fname,  _PART_BCH_STR_LEN, filename);
    fname[_PART_BCH_STR_LEN - 1] = '\0'; // Allways null-terminate

    for (int i=0; i<BATCHSIZE; i++)
    {
        projectiveSpaces->stack[i] = (long *) malloc(sizeof(long) * n);
        if (projectiveSpaces->stack[i] == NULL)
        {
            FakeProjectiveSpacesDeInit(projectiveSpaces);
            __log_err_malloc();
            return NULL;
        }
    }

    return projectiveSpaces;
}


void FakeProjectiveSpacesDeInit(FakeProjectiveSpaces_t *fakeProjectiveSpaces)
{
    for (int i=0; i<BATCHSIZE; i++)
        free(fakeProjectiveSpaces->stack[i]);

    fclose(fakeProjectiveSpaces->_file);
    free(fakeProjectiveSpaces);
}


void FakeProjectiveSpacesDump(FakeProjectiveSpaces_t *fakeProjectiveSpaces, long *v, bool forceFlush)
{
    FILE *f   = fakeProjectiveSpaces->_file;
    char *_fp = fakeProjectiveSpaces->_fnameprefix;
    int  *_sc = &(fakeProjectiveSpaces->_stackcounter);
    int  *_bc = &(fakeProjectiveSpaces->_batchcounter);
    int  n    = fakeProjectiveSpaces->n;

    memcpy(fakeProjectiveSpaces->stack[*_sc], v, sizeof(long) * n);

    if (++(*_sc) < BATCHSIZE && !forceFlush)
        return;
    
    FakeProjectiveSpacesFlush(fakeProjectiveSpaces);
}


void FakeProjectiveSpacesFlush(FakeProjectiveSpaces_t *projectiveSpaces)
{
    FILE *f   = projectiveSpaces->_file;
    int  *_sc = &(projectiveSpaces->_stackcounter);
    int  *_bc = &(projectiveSpaces->_batchcounter);
    int  n    = projectiveSpaces->n;

    __log_dbg_flush(*_bc);

    for (int i = 0; i < *_sc; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(f, j==(n-1) ?"%ld\n":"%ld,", projectiveSpaces->stack[i][j]);

    (*_bc)++;
    (*_sc) = 0;
}


void FakeProjectiveSpacesDeterminantQ(FakeProjectiveSpaces_t *projectiveSpaces, long *v)
{
    if (DET_FUNC_PARSED_00(v) == 0)
        FakeProjectiveSpacesDump(projectiveSpaces, v, false);
}


void FakeProjectiveSpacesPartition(FakeProjectiveSpaces_t *projectiveSpaces, int toPart, int numWorkers) {

    int n = projectiveSpaces->n;
    long *v = (long *) malloc(sizeof(long) * n); // On stack, only const array sizes.
    
    for (int j = 0; j < n; ++j) {
        v[j] = 1;
    }
    
    long cap = toPart - n + 1;
    long i, s;
    
    v[0] = cap;

    FakeProjectiveSpacesDeterminantQ(projectiveSpaces, v);
    
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

    FakeProjectiveSpacesFlush(projectiveSpaces);
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