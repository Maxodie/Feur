#pragma once

char* FE_DECL FE_StringFormatV(const char* format, va_list* va_listp);
char* FE_DECL FE_StringFormatAlloc(const char* format, ...);
void FE_DECL FE_StringFormatFree(char* str);