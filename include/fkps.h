#ifndef _FKPS_H
#define _FKPS_H

#include <stdbool.h>
#include <stdio.h>

#include "fkpscdefs.h"

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
bool FakeProjectiveSpacesAssignTriplet(
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
 * Appends the current tripolet to the stack,
 * ocationally flushing it to the file
 * if it's `_base_pointer` is at `BATCH_SIZE`
 * or if `forceFlush` is true.
*/
void FakeProjectiveSpacesDump(
    FakeProjectiveSpaces_t *projectiveSpaces,
    bool forceFlush);

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
    Saves all the possible solutions to the
    stack.
    Runs on a loop.
    It is NOT thread safe, so
    one thread only per `FakeProjectiveSpaces_t`.
*/
void FakeProjectiveSpacesSolvePartial(
    FakeProjectiveSpaces_t *projectiveSpaces,
    FkpsType_t toPart
    );


#endif /* _FKPS_H */