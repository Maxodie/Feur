#pragma once

typedef enum {
    LOG_DEBUG,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR,
    LOG_LEVEL_LEN
} LOG_LEVEL;

void ulogger_log(LOG_LEVEL level, const char* fmt, ...);

#define FE_CORE_LOG_DEBUG(...) ulogger_log(LOG_DEBUG, __VA_ARGS__)
#define FE_CORE_LOG_SUCCESS(...) ulogger_log(LOG_SUCCESS, __VA_ARGS__)
#define FE_CORE_LOG_WARN(...) ulogger_log(LOG_WARNING, __VA_ARGS__)
#define FE_CORE_LOG_ERROR(...) ulogger_log(LOG_ERROR, __VA_ARGS__)

#define FE_LOG_DEBUG(...) ulogger_log(LOG_DEBUG, __VA_ARGS__)
#define FE_LOG_SUCCESS(...) ulogger_log(LOG_SUCCESS, __VA_ARGS__)
#define FE_LOG_WARN(...) ulogger_log(LOG_WARNING, __VA_ARGS__)
#define FE_LOG_ERROR(...) ulogger_log(LOG_ERROR, __VA_ARGS__)