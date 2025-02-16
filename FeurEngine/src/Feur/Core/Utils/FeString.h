#pragma once

char* FE_DECL FE_StringFormatAlloc(const char* format, ...);
void FE_DECL FE_StringFormat(void* dst, const char* format, ...);
void FE_DECL FE_StringWrite(char* dst, SizeT length, const char* format, va_list* va_listp);
void FE_DECL FE_StringFormatFree(char* str);