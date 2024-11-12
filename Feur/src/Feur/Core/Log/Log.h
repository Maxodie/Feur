#pragma once

typedef enum {
    LOG_DEBUG,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR,
    LOG_LEVEL_LEN
} LOG_LEVEL;

void FE_DECL FE_LoggerLog(const char* prefix, LOG_LEVEL level, const char* fmt, ...);
void FE_DECL FE_ContextLoggerLog(const char* prefix, LOG_LEVEL level, const char* functionCtx, const char* fileCtx, Uint32 lineCtx, const char* fmt, ...);

#define FE_CORE_LOG_DEBUG(...) FE_LoggerLog("CORE", LOG_DEBUG, __VA_ARGS__)
#define FE_CORE_LOG_SUCCESS(...) FE_LoggerLog("CORE", LOG_SUCCESS, __VA_ARGS__)
#define FE_CORE_LOG_WARNING(...) FE_ContextLoggerLog("CORE", LOG_WARNING, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define FE_CORE_LOG_ERROR(...) FE_ContextLoggerLog("CORE", LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)

#define FE_LOG_DEBUG(...) FE_LoggerLog("CLIENT", LOG_DEBUG, __VA_ARGS__)
#define FE_LOG_SUCCESS(...) FE_LoggerLog("CLIENT", LOG_SUCCESS, __VA_ARGS__)
#define FE_LOG_WARNING(...) FE_ContextLoggerLog("CLIENT", LOG_WARNING, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)
#define FE_LOG_ERROR(...) FE_ContextLoggerLog("CLIENT", LOG_ERROR, __FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)