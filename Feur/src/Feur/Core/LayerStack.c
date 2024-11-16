#include "fepch.h"

#include "Feur/Core/LayerStack.h"

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackInit(LayerStack* layerStack)
{
	FE_ListInit(layerStack->stackedlayers)
	FE_ListReserve(layerStack->stackedlayers, 3);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPop(LayerStack* layerStack)
{
	FE_ListPop(layerStack->stackedlayers);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackInsert(LayerStack* layerStack, Layer* value, Uint32 position)
{
	FE_ListInsert(layerStack->stackedlayers, value, position);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPush(LayerStack* layerStack, Layer* value)
{
	FE_ListPush(layerStack->stackedlayers, value);
}

FE_FORCEINLINE_FUN SizeT FE_DECL FE_LayerStackGetCount(LayerStack* layerStack)
{
	return layerStack->stackedlayers.impl.count;
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackClear(LayerStack* layerStack)
{
	FE_ListClear(layerStack->stackedlayers);
}
