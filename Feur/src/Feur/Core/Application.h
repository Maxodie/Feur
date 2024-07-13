#pragma once

struct FE_Event;
struct FE_EventData;

typedef struct FE_App
{
	WindowData windowData;
	LayerStack layerStack;
} FE_App;

void StartApp_impl();
void RunApp_impl();

void StartApp();

void AddLayerApp(Layer* newLayer);
void InsertLayerApp(Layer* newLayer, Uint32 position);
void PopLayerApp();
void AppUpdate();
void LoadWindow();
void PullWindowEvent();
void Render();
void AppOnEvent(FE_Event event);
BOOL OnWindowResizing(FE_EventData* windowResizeEvent);
BOOL OnWindowClose(FE_EventData* windowResizeEvent);

void ShutdownApp();
void QuitApp();

const FE_App* GetApp();

// TODO : some functions does not need to be imported on sandbox, put those function in other headers (_internal) and create utils to put list and weird nerd stuff