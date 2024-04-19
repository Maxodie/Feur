#pragma once

typedef enum {
    LOG_DEBUG,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR,
    LOG_LEVEL_LEN
} LOG_LEVEL;

void ulogger_log(const char* prefix, LOG_LEVEL level, const char* fmt, ...);

#define FE_CORE_LOG_DEBUG(...) ulogger_log("CORE", LOG_DEBUG, __VA_ARGS__)
#define FE_CORE_LOG_SUCCESS(...) ulogger_log("CORE", LOG_SUCCESS, __VA_ARGS__)
#define FE_CORE_LOG_WARNING(...) ulogger_log("CORE", LOG_WARNING, __VA_ARGS__)
#define FE_CORE_LOG_ERROR(...) ulogger_log("CORE", LOG_ERROR, __VA_ARGS__)

#define FE_LOG_DEBUG(...) ulogger_log("CLIENT", LOG_DEBUG, __VA_ARGS__)
#define FE_LOG_SUCCESS(...) ulogger_log("CLIENT", LOG_SUCCESS, __VA_ARGS__)
#define FE_LOG_WARNING(...) ulogger_log("CLIENT", LOG_WARNING, __VA_ARGS__)
#define FE_LOG_ERROR(...) ulogger_log("CLIENT", LOG_ERROR, __VA_ARGS__)