#pragma once

typedef struct LayerStack
{
	SizeT count;
	FE_List(Layer*) stackedlayers;

} LayerStack;


// TODO : Canva layer handling


void FE_API InitLayerStack(LayerStack* layerStack);
void FE_API PopLayerStack(LayerStack* layerStack);
void FE_API InsertLayerStack(LayerStack* layerStack, Layer* value, Uint32 position);
void FE_API PushLayerStack(LayerStack* layerStack, Layer* value);