#pragma once

typedef struct LayerStack
{
	size_t count;
	Layer** dataPtr;

} LayerStack;


// TODO : Canva layer handling


void InitLayerStack(LayerStack* layerStack);
void PopLayerStack(LayerStack* layerStack); 
void InsertLayerStack(LayerStack* layerStack, Layer* value, Uint32 position);
void PushLayerStack(LayerStack* layerStack, Layer* value);