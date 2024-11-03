#include "fepch.h"
#include "Feur/Core/Utils/FeurSort.h"

Int32 FE_API Fe_SortInt32Ascending(const void* a, const void* b)
{
	return *((Int32*)a) > *((Int32*)b);
}