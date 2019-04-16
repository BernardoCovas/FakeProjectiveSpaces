#ifndef _LIBFKPS_CONFIG_H
#define _LIBFKPS_CONFIG_H


/*
 * Batch Size, when batch is created
 * with `LibFkpsBatchNew()`.
 * Does not influence memory usage.
 */
#define LIBFKPS_BATCHSIZE 100000000;

/*
 * The size of the stack, before having
 * to be flushed.
 */
#define LIBFKPS_STACKSIZE 1000000

/*
 * Compile command used when not using CUDA.
 */
#define LIBFKPS_COMPILE_COMMAND "gcc %i -o %o -shared -O3"

/*
 * Internal folder name.
 */
#define LIBFKPS_FOLDER_INTERNAL ".fkps"

/*
 * Folder to store the solutions.
 */

#define LIBFKPS_SOLVED_FOLDER "solved"

/*
 * Use CUDA. Set in CMakeLists.txt.
 */
// #define LIBFKPS_USE_CUDA


#endif /* _LIBFKPS_CONFIG_H */