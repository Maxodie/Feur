#pragma once

typedef struct LayerStack
{
	size_t count;
	Layer** dataPtr;

} LayerStack;


// TODO : Canva layer handling


void FE_API InitLayerStack(LayerStack* layerStack);
void FE_API PopLayerStack(LayerStack* layerStack);
void FE_API InsertLayerStack(LayerStack* layerStack, Layer* value, Uint32 position);
void FE_API PushLayerStack(LayerStack* layerStack, Layer* value);