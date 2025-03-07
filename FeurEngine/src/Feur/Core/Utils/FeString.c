#include "fepch.h"
#include "Feur/Core/Utils/FeString.h"

char* FE_DECL FE_StringFormatAlloc(const char* format, ...)
{
    FE_CORE_ASSERT(format != NULL, "char* format buffer is NULL");

	va_list list;
	va_start(list, format);

	SizeT length = vsnprintf(NULL, 0, format, list);
	char* buffer = FE_MemoryGeneralAlloc(length + 1);

	FE_StringWrite(buffer, length, format, &list);
	va_end(list);
	return buffer;
}

void FE_DECL FE_StringFormat(void* dst, const char* format, ...)
{
    FE_CORE_ASSERT(dst != NULL, "void* dst buffer is NULL");
    FE_CORE_ASSERT(format != NULL, "char* format buffer is NULL");

	va_list list;
	va_start(list, format);

	SizeT length = vsnprintf(NULL, 0, format, list);
	FE_StringWrite(dst, length, format, &list);

	va_end(list);
}

void FE_DECL FE_StringWrite(char* dst, SizeT length, const char* format, va_list* va_listp)
{
    FE_CORE_ASSERT(dst != NULL, "void* dst buffer is NULL");
    FE_CORE_ASSERT(format != NULL, "char* format buffer is NULL");
    FE_CORE_ASSERT(va_listp != NULL, "va_list* va list ptr buffer is NULL");

	vsnprintf(dst, length + 1, format, *va_listp);
	dst[length] = '\0';
}

void FE_DECL FE_StringFormatFree(char* str)
{
	FE_MemoryGeneralFree(str);
}
