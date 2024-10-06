#pragma once

void FE_API NuklearGUILayerInit();
	 FE_API
void FE_API NuklearGUILayerEvent(FE_Event* event);
void FE_API NuklearGUILayerUpdate();
void FE_API NuklearGUILayerRender(Layer* layer);
void FE_API NuklearGUILayerOnAttach(Layer* layer);
void FE_API NuklearGUILayerOnDetach();

Layer FE_API CreateNewNuklearGUILayer(char* layerName);