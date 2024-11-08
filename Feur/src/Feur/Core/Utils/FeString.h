#pragma once

char* FE_API FE_StringFormatV(const char* format, va_list* va_listp);
char* FE_API FE_StringFormatAlloc(const char* format, ...);
void FE_API FE_StringFormatFree(char* str);