#include "fepch.h"
#include "Feur/Core/Utils/Optional.h"

void FE_OptionalSetValue_impl(Bool* hasValue, Byte* data, const void* value, SizeT dataSize)
{
	*hasValue = TRUE;

	memcpy(data, value, dataSize);
}
