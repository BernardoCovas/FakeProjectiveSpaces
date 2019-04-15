#ifndef _LIBFKPS_H
#define _LIBFKPS_H

typedef void* FKPS;
typedef void* FKPSBatch;

typedef enum
{
	LIBFKPS_ERR_SUCCESS,
	LIBFKPS_ERR_MEMORY,
	LIBFKPS_ERR_LIB_NOT_FOUND,
	LIBFKPS_ERR_SRC_NOT_FOUND,
	LIBFKPS_ERR_SOL_NOT_FOUND,
	LIBFKPS_ERR_CREATE_DIRS,
	LIBFKPS_ERR_COMPILE,
	LIBFKPS_ERR_PARTITION_END,
	LIBFKPS_ERR_PARTITION_INIT,
	LIBFKPS_ERR_PARTITION_INDEX_RANGE,
	LIBFKPS_ERR_PARTITION_FULL,
} LibFkpsErr_t;


/*
 * Return the (char*) representation 
 * of an error.
 */
const char* LibFkpsErrToChar(LibFkpsErr_t);


/*
 * Initializes the struct.
 */
LibFkpsErr_t LibFkpsInit(FKPS* lib, int N, int K, const char* detExprs);


/*
 * Releases every resource allocated to `lib`.
 */
LibFkpsErr_t LibFkpsDeinit(FKPS lib);


/*
 * Generates the C/CUDA file to be compiled.
 */
LibFkpsErr_t LibFkpsGenerate(FKPS lib);


/*
 * Compiles the generated C or CUDA (ptx) file.
 */
LibFkpsErr_t LibFkpsCompile(FKPS lib);


/*
 * Loads the function to memory.
 * Must be compiled.
 * Returns `LIBFKPS_ERR_SUCCESS` if loaded,
 * anything else on error.
 */
LibFkpsErr_t LibFkpsLoad(FKPS lib);


/*
 * Initializes a batch.
 */
LibFkpsErr_t LibFkpsBatchInit(FKPS lib, FKPSBatch* batch);


/*
 * Frees all resources associated with a batch.
 */
LibFkpsErr_t LibFkpsBatchFree(FKPSBatch batch);


/*
 * Increments the batch vector by one.
 */
LibFkpsErr_t LibFkpsBatchIncrement(FKPSBatch batch);


/*
 * Allocates and generates a new
 * batch from `state`.
 * Changes `state` in place.
 */
LibFkpsErr_t LibFkpsBatchNew(FKPSBatch state, FKPSBatch* outBatch);


/*
 * Sets the batch index `i` to a copy of the vector `v`.
 */
LibFkpsErr_t LibFkpsBatchAdd(FKPSBatch batch, int *v);


/*
 * Sets the pointer `outV` to the location of the asked index.
 */
LibFkpsErr_t LibFkpsBatchGet(FKPSBatch batch, int index, int** outV);


/*
 * Writes the partitions in `batch` to the file.
 */
LibFkpsErr_t LibFkpsBatchFlush(FKPSBatch batch, FKPS lib);


/*
 * Computes the `batch` on `lib`. Stores
 * the valid partitions in `batch`.
 * Returns when `batch`'s partitions
 * are full, when computation is done,
 * or when any other error occurs, returning
 * the corresponding errors.
 */
LibFkpsErr_t LibFkpsBatchCompute(FKPSBatch batch, FKPS lib);


#endif /* _LIBFKPS_H */