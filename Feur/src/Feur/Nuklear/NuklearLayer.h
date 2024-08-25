#pragma once

void NuklearGUILayerInit();

void NuklearGUILayerEvent(FE_Event* event);
void NuklearGUILayerUpdate();
void NuklearGUILayerRender(Layer* layer);
void NuklearGUILayerOnAttach(Layer* layer);
void NuklearGUILayerOnDetach();

Layer CreateNewNuklearGUILayer(char* layerName);