#ifndef _LIBFKPS_CONFIG_H
#define _LIBFKPS_CONFIG_H


/*
 * Batch Size computed by each thread.
 */
#define LIBFKPS_THREAD_BATCHSIZE 10000;

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