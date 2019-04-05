#ifndef _LIBFKPSCONFIG_H
#define _LIBFKPSCONFIG_H


/**
 * Number of parallel workers.
 * */
#define FKPS_COMPUTE_PARALELL 8


/* ONE OF THESE NEXT OPTIONS */ 

/**
 * Speeds up the computation of
 * a single determinant.
 * Solves each compiled lib sequentially,
 * but parallelizes it's computations.
 * */
#define FKPS_COMPUTE_PARALELL_SINGLELIB

/**
 * Speeds up the computation of multiple
 * compiled libs. It's more efficient
 * than the previous option, but a single lib
 * still takes as long to finish as a sequential
 * computation.
 * */
// #define FKPS_COMPUTE_PARALELL_MULTILIB


/**
 * The size of the stack holding the solutions
 * before flushing them to disk.
 * */
#define FKPS_STACKSIZE 1000000

/**
 * The size of the generated integer
 * partitions batch that a single 
 * thread computes. The ideal value
 * is not exact science, play arround
 * with it until you get the best results.
 * You should be able to get 100% CPU usage.
 * */
#define FKPS_MINIBATCH_SIZE 10000


#endif // _LIBFKPSCONFIG_H