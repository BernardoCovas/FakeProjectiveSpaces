#ifndef _LIBFKPSLOGGING_HH
#define _LIBFKPSLOGGING_HH

#include "LibFkpsDeterminantQ.hh"


void __log_err_malloc();
void __log_err_fopen(const char * fname);

void __fkps_err_generate_parse(const char * fname, int line);
void __fkps_dbg_generate(const char * fname);

void __log_dbg_flush(int batch, const char *  fname);
void __fkps_log_libloaded(LibfkpsDeterminantQ_t *lib);
void __fkps_err_libloaded(const char * fname);
void __fkps_log_started(LibfkpsDeterminantQ_t *lib);
void __log_dbg_unloading(const char * fname);

void __fkps_log_compile_res(int res, const char * command);
void __fkps_err_compile_cmd(const char * command);

#endif // _LIBFKPSLOGGING_HH
