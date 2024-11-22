#include "fepch.h"

#include "Feur/Core/LayerStack.h"

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackInit(LayerStack* layerStack)
{
	FE_ListInit(layerStack->stackedlayers)
	FE_ListReserve(layerStack->stackedlayers, 3);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPop(LayerStack* layerStack)
{
	layerStack->stackedlayers.data[layerStack->stackedlayers.impl.count - 1]->OnDetach();
	FE_ListPop(layerStack->stackedlayers);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackInsert(LayerStack* layerStack, Layer* value, Uint32 position)
{
	FE_ListInsert(layerStack->stackedlayers, value, position);
	layerStack->stackedlayers.data[layerStack->stackedlayers.impl.count - 1]->OnAttach(value);
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPush(LayerStack* layerStack, Layer* value)
{
	FE_ListPush(layerStack->stackedlayers, value);
	layerStack->stackedlayers.data[layerStack->stackedlayers.impl.count - 1]->OnAttach(value);
}

FE_FORCEINLINE_FUN SizeT FE_DECL FE_LayerStackGetCount(LayerStack* layerStack)
{
	return layerStack->stackedlayers.impl.count;
}

FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackClear(LayerStack* layerStack)
{
	for (SizeT i = 0; i < layerStack->stackedlayers.impl.count; i)
	{
		FE_LayerStackPop(layerStack);
	}

	FE_ListClear(layerStack->stackedlayers);
}
