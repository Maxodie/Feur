#include "fepch.h"
#include "Feur/Core/Utils/ByteFlag.h"

void FE_DECL FE_FlagInit(FE_ByteFlag* flag)
{
	FE_ListInit(*flag);
	FE_ListPushValue(*flag, Byte, 0);
}

void FE_DECL FE_FlagDestroy(FE_ByteFlag* flag)
{
	FE_ListClear(*flag);
}

void FE_DECL FE_FlagReset(FE_ByteFlag* flag)
{
	memset(flag->data, 0, flag->impl.count); // Byte is 1
}

void FE_FlagSet(FE_ByteFlag* flag , Uint64 newFlag)
{
	FE_CORE_ASSERT(flag->impl.isInitialized, "ByteFlag has not been initialized");

	Uint64 flagBit = newFlag / 8;

	if (flag->impl.count <= flagBit)
	{
		Uint64 amountToAdd = flagBit - (flag->impl.count - 1);

		Byte arr[] = {0};
		FE_ListPushArray(*flag, arr, amountToAdd);
		memset(flag->data + flag->impl.count - amountToAdd, 0, amountToAdd);
	}

	flag->data[flagBit] |= BIT(newFlag % 8);
}

Bool FE_FlagExist(FE_ByteFlag* flag, Uint64 searchedFlag)
{
	FE_CORE_ASSERT(flag->impl.isInitialized, "ByteFlag has not been initialized");

	Uint64 flagBit = searchedFlag / 8;

	if (flag->impl.count < flagBit)
	{
		return FALSE;
	}

	return flag->data[flagBit] & BIT(searchedFlag % 8);
}

void FE_FlagRemove(FE_ByteFlag* flag, Uint64 flagToRemove)
{
	FE_CORE_ASSERT(flag->impl.isInitialized, "ByteFlag has not been initialized");

	Uint64 flagBit = flagToRemove / 8;

	if (flag->impl.count < flagBit)
	{
		return;
	}

	flag->data[flagBit] &= ~BIT(flagToRemove % 8);
}

void FE_FlagPrint(FE_ByteFlag* flag)
{
	char* result = FE_MemoryGeneralAlloc(flag->impl.count);
	SizeT bitCount = 0;
	for (SizeT i = 0; i < (flag->impl.count * 8) * 2 - 1; i++)
	{
		if (i % 2 == 0)
		{
			result[i] =  ((flag->data[bitCount / 8] & BIT(bitCount % 8)) ? 1  : 0)  + '0';
			bitCount++;
		}
		else
		{
			result[i] = '-';
		}
	}

	FE_CORE_LOG_DEBUG("%s", result);
	FE_MemoryGeneralFree(result);
}
