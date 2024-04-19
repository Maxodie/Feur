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
void get_time() {
    time(&current_time);
    m_time = localtime(&current_time);
}

void ulogger_log(const char* prefix, LOG_LEVEL level, const char* fmt, ...) {

    va_list args;
    va_start(args, fmt);
    get_time();
#ifndef NO_ANSI 
    printf("%s", colors[level]);
#endif

    /*printf("[%d/%d/%d -> %d:%d:%d][%s_%s] ", m_time->tm_mday,
        m_time->tm_mon,
        m_time->tm_year + 1900,
        m_time->tm_hour,
        m_time->tm_min,
        m_time->tm_sec, 
        prefix,
        type[level]);*/
        printf("[%d:%d:%d][%s_%s] ",
            m_time->tm_hour,
            m_time->tm_min,
            m_time->tm_sec,
            prefix,
            type[level]);
    vfprintf(stdout, fmt, args);
    printf("\n%s", colors[LOG_DEBUG]);
    va_end(args);
}