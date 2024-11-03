#include <fepch.h>
#include "Log.h"

#ifdef __EMSCRIPTEN
#define NO_ANSI
#endif

char* type[LOG_LEVEL_LEN] = {
    "DEBUG",
    "SUCCESS",
    "WARNING",
    "ERROR"
};

char* colors[LOG_LEVEL_LEN] = {
    "\x1b[0m",
    "\x1b[32m",
    "\x1b[1;33m",
    "\x1b[31m"
};

time_t current_time;
struct tm* m_time;
void FE_LoggerGetTime() {
    time(&current_time);
    m_time = localtime(&current_time);
}

void FE_API FE_PrefixLog(const char* prefix, LOG_LEVEL level)
{
    FE_LoggerGetTime();

#ifndef NO_ANSI 
    printf("%s", colors[level]);
#endif

    printf("[%d:%d:%d][%s_%s] ",
        m_time->tm_hour,
        m_time->tm_min,
        m_time->tm_sec,
        prefix,
        type[level]);
}

void FE_API FE_SuffixLog()
{
    printf("\n%s", colors[LOG_DEBUG]);
}

void FE_API FE_LoggerLog(const char* prefix, LOG_LEVEL level, const char* fmt, ...) {

    va_list args;
    va_start(args, fmt);

    FE_PrefixLog(prefix, level);
    
    switch (level)
    {
    case LOG_ERROR:
        vfprintf(stderr, fmt, args);
        break;
    default:
        vfprintf(stdout, fmt, args);
        break;
    }
    
    FE_SuffixLog();

    va_end(args);
}



void FE_API FE_ContextLoggerLog(const char* prefix, LOG_LEVEL level, const char* functionCtx, const char* fileCtx, Uint32 lineCtx, const char* fmt, ...) 
{

    va_list args;
    va_start(args, fmt);

    FE_PrefixLog(prefix, level);

    printf("%s() from %s, line %d : ", functionCtx, fileCtx, lineCtx);

    switch (level)
    {
    case LOG_ERROR :
        vfprintf(stderr, fmt, args);
        break;
    default:
        vfprintf(stdout, fmt, args);
        break;
    }
    

    FE_SuffixLog();

    va_end(args);
}