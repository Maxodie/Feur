#pragma once

void FE_DECL NuklearGUILayerInit();

void FE_DECL NuklearGUILayerEvent(FE_Event* event);
void FE_DECL NuklearGUILayerUpdate();
void FE_DECL NuklearGUILayerRender(Layer* layer);
void FE_DECL NuklearGUILayerOnAttach(Layer* layer);
void FE_DECL NuklearGUILayerOnDetach();

Layer FE_DECL CreateNewNuklearGUILayer(char* layerName);