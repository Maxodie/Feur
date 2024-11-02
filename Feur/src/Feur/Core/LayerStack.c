#include "fepch.h"

#include "Feur/Core/LayerStack.h"

FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackInit(LayerStack* layerStack)
{
	if (FE_ListInit(layerStack->stackedlayers))
	{
		return FE_ListReserve(layerStack->stackedlayers, 3);
	}

	return FALSE;
}

FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackPop(LayerStack* layerStack)
{
	return FE_ListPop(layerStack->stackedlayers);
}

FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackInsert(LayerStack* layerStack, Layer* value, Uint32 position)
{
	return FE_ListInsert(layerStack->stackedlayers, value, position);
}

FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackPush(LayerStack* layerStack, Layer* value)
{
	return FE_ListPush(layerStack->stackedlayers, value);
}

FE_FORCEINLINE_FUN SizeT FE_API FE_LayerStackGetCount(LayerStack* layerStack)
{
	return layerStack->stackedlayers.impl.count;
}
