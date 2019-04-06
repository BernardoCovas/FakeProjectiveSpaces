#ifndef _FKPSDETERMINANTQ_HH
#define _FKPSDETERMINANTQ_HH

#include <stdio.h>

#include <string>
#include <vector>
#include <mutex>

typedef struct
{
    int        libinfo_N;
    int        libinfo_K;
    int     (* determinantQ )(int *x);

    FILE     * file;
    void     * handle;

    std::string *filename;
    std::string *libname;
    
    int      * _partitions;

    int        _stackcounter;
    int        _batchcounter;

    std::mutex * _mutex; // std::mutex is non-copiable or moovable
} LibfkpsDeterminantQ_t;


void __log_err_malloc(const char * str);
void __log_err_fopen(const char * fname);
void __log_dbg_flush(int batch, const char *  fname);
void __log_dbg_unloading(const char * fname);
void __fkps_log_libloaded(LibfkpsDeterminantQ_t *lib);
void __fkps_err_libloaded(const char * fname);
void __fkps_log_started(LibfkpsDeterminantQ_t *lib);

void __fkps_log_compile_res(int res, const char * command);

#endif // _FKPSDETERMINANTQ_HH
