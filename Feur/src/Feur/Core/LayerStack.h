#pragma once

typedef struct LayerStack
{
	FE_List(Layer*) stackedlayers;

} LayerStack;


// TODO : Canva layer handling


FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackInit(LayerStack* layerStack);
FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackPop(LayerStack* layerStack);
FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackInsert(LayerStack* layerStack, Layer* value, Uint32 position);
FE_FORCEINLINE_FUN Bool FE_API FE_LayerStackPush(LayerStack* layerStack, Layer* value);
FE_FORCEINLINE_FUN SizeT FE_API FE_LayerStackGetCount(LayerStack* layerStack);