#pragma once

typedef struct LayerStack
{
	FE_List(Layer*) stackedlayers;
	SizeT startOverlayIndex;

} LayerStack;


// TODO : Canva layer handling


FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackInit(LayerStack* layerStack);
FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPop(LayerStack* layerStack);
FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPushOvelay(LayerStack* layerStack, Layer* value);
FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackRemoveLayer(LayerStack* layerStack, Layer* value);
FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackPush(LayerStack* layerStack, Layer* value);
FE_FORCEINLINE_FUN SizeT FE_DECL FE_LayerStackGetCount(LayerStack* layerStack);
FE_FORCEINLINE_FUN void FE_DECL FE_LayerStackClear(LayerStack* layerStack);