#include "LibFkpsDeterminantQ.hh"

#include "LibFkpsLogging.hh"

#include <sstream>
#include <atomic>


void __fkps_dbg(const char *str)
{
    static std::atomic_int currLog = 0;
    printf("DBG: [ %d ][ %s ]\n", currLog++, str);
}

void __fkps_err(const char *str)
{
    static std::atomic_int currLog = 0;
    printf("ERR: [ %d ][ %s ]\n", currLog++, str);
}

void __log_err_malloc()
{
    __fkps_err("Could not allocate enough resources.");
}

void __log_err_fopen(const char * fname)
{
    std::stringstream log;
    log << "Could not open: " << fname;
    __fkps_err(log.str().c_str());
}

void __fkps_err_generate_parse(const char * fname, int line)
{
    std::stringstream log;
    log << "Cound not parse: " << fname << ", line: " << line << '.';
    __fkps_err(log.str().c_str());
}

void __fkps_dbg_generate(const char * fname)
{
    std::stringstream log;
    log << "Wrote: " << fname << ".";
    __fkps_dbg(log.str().c_str());
}

void __log_dbg_flush(int batch, const char * fname)
{
    std::stringstream log;
    log << "Flushing batch " << batch << " to " << fname;
    __fkps_dbg(log.str().c_str());
}

void __log_dbg_unloading(const char * fname)
{
    std::stringstream log;
    log << "Unloading: " << fname;
    __fkps_dbg(log.str().c_str());
}

void __fkps_log_libloaded(LibfkpsDeterminantQ_t *lib)
{
    std::stringstream log;
    log << "Using library: " << lib->libname->c_str() << ", Writing to: " << lib->filename->c_str();
    __fkps_dbg(log.str().c_str());
}

void __fkps_err_libloaded(const char * fname)
{
    std::stringstream log;
    log << "Failed loading: " << fname;
    __fkps_err(log.str().c_str());
}


void __fkps_log_started(LibfkpsDeterminantQ_t *lib)
{
    std::stringstream log;
    log << "Started: " << lib->libname->c_str();
    __fkps_dbg(log.str().c_str());
}

void __fkps_log_compile_res(int res, const char *command)
{
    std::stringstream log;
    log << "Compile result: " << res << " for command: " << command;
    __fkps_dbg(log.str().c_str());
}

void __fkps_err_compile_cmd(const char * command)
{
    std::stringstream log;
    log << 
    "Wrong compile command: '" 
    << command << 
    "'. Should contain a '%i' and a '%o' "
    "to be replaced with the input and output" 
    "filenames, respectively";

    __fkps_err(log.str().c_str());
}
