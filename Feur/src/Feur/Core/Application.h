#pragma once

struct FE_Event;
struct FE_EventData;

typedef struct FE_App
{
	WindowData windowData;
	RendererData rendererData;
	LayerStack layerStack;

	ClockT startTime;
	ClockT endTime;
	Uint32 targetFps;
	NuklearGUIInterface guiInterface;

	FE_EntityRegistry ecsRegistry;
	FE_EntityComponentTypeID cam3DComp;
	FE_EntityComponentTypeID meshComp;
	FE_ECSSystemContext ecsContext;
} FE_App;

void FE_DECL StartApp_impl();
void FE_DECL RunApp_impl();

void FE_DECL StartApp();
Double FE_DECL GetDeltaTime();

void FE_DECL AppPrepareRender();
void FE_DECL AppUpdate(Double deltaTime);

void FE_DECL ConsumeDeltaTime(Double deltaTime);

void FE_DECL AddLayerApp(Layer* newLayer);
void FE_DECL InsertLayerApp(Layer* newLayer, Uint32 position);
void FE_DECL PopLayerApp();
void FE_DECL LoadWindow();
void FE_DECL PullWindowEvent();
void FE_DECL AppOnEvent(FE_Event event);
Bool FE_DECL OnWindowResizing(FE_EventData* windowResizeEvent);
Bool FE_DECL OnWindowClose(FE_EventData* windowResizeEvent);

void FE_DECL ShutdownApp();
void FE_DECL QuitApp();

const FE_App* FE_DECL GetApp();

// TODO : some functions does not need to be imported on sandbox, put those function in other headers (_internal) and create utils to put list and weird nerd stuff
