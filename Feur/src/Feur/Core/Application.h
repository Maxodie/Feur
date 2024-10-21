#pragma once

struct FE_Event;
struct FE_EventData;

typedef struct FE_App
{
	WindowData windowData;
	RendererAPIData rendererAPIData;
	LayerStack layerStack;
} FE_App;

void FE_API StartApp_impl();
void FE_API RunApp_impl();

void FE_API StartApp();
void FE_API AppUpdate();

void FE_API AddLayerApp(Layer* newLayer);
void FE_API InsertLayerApp(Layer* newLayer, Uint32 position);
void FE_API PopLayerApp();
void FE_API LoadWindow();
void FE_API PullWindowEvent();
void FE_API Render();
void FE_API AppOnEvent(FE_Event event);
Bool FE_API OnWindowResizing(FE_EventData* windowResizeEvent);
Bool FE_API OnWindowClose(FE_EventData* windowResizeEvent);

void FE_API ShutdownApp();
void FE_API QuitApp();

const FE_App* GetApp();

// TODO : some functions does not need to be imported on sandbox, put those function in other headers (_internal) and create utils to put list and weird nerd stuff
