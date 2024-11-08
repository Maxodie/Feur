#include "fepch.h"
#include "Feur/Core/Utils/FeString.h"

char* FE_API FE_StringFormatV(const char* format, va_list* va_listp)
{
	if (format == NULL || va_listp == NULL)
	{
		FE_CORE_LOG_ERROR("failed format, format or va_list is null");
		return NULL;
	}

	SizeT length = vsnprintf(NULL, 0, format, *va_listp);
	char* buffer = FE_MemoryGeneralAlloc(length + 1);
	if (!buffer)
	{
		return NULL;
	}

	vsnprintf(buffer, length + 1, format, *va_listp);
	buffer[length] = '\0';
	return buffer;
}

char* FE_API FE_StringFormatAlloc(const char* format, ...)
{
	if (!format)
	{
		FE_CORE_LOG_ERROR("failed format, format is null");
		return NULL;
	}

	va_list list;
	va_start(list, format);
	char* result = FE_StringFormatV(format, &list);
	va_end(list);
	return result;
}

void FE_API FE_StringFormatFree(char* str)
{
	FE_MemoryGeneralFree(str);
}
