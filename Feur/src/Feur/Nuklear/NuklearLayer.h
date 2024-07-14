#pragma once

void NuklearGUILayerInit();

void NuklearGUILayerUpdate();
void NuklearGUILayerEvent(FE_Event* event);
void NuklearGUILayerOnAttach();
void NuklearGUILayerOnDetach();

Layer CreateNewNuklearGUILayer(const char* layerName);