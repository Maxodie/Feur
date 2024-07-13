#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Core/Event/Event.h"
#include "Feur/Core/Input/Input.h"

#include "nuklear/nuklear.h"

static FE_App g_fe_App;

static BOOL g_IsAppRunning = TRUE;

void StartApp_impl()
{
	StartApp();
}

void RunApp_impl()
{
	while (g_IsAppRunning)
	{
		PullWindowEvent();
		AppUpdate();
		Render();
	}

	ShutdownApp();
}


void AppUpdate()
{
	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		g_fe_App.layerStack.dataPtr[i]->OnUpdate();
	}
}


void StartApp()
{
	LoadWindow();
	InitInputAPI();
	InitLayerStack(&g_fe_App.layerStack);
}

void AddLayerApp(Layer* newLayer)
{
	PushLayerStack(&g_fe_App.layerStack, newLayer);
	newLayer->OnAttach();
}

void InsertLayerApp(Layer* newLayer, Uint32 position)
{
	InsertLayerStack(&g_fe_App.layerStack, newLayer, position);
}

void PopLayerApp()
{
	PopLayerStack(&g_fe_App.layerStack);
}

void LoadWindow()
{
	InitWindowAPI();
	CreateWindow(&g_fe_App.windowData);

	g_fe_App.windowData.EventCallback = AppOnEvent;
}

void AppOnEvent(FE_Event event)
{
	FE_EventDispatcher eventDispatcher = { .eventType = event.eventType, .event = event };
	DispatchEvent(&eventDispatcher, FE_Event_WindowResize, OnWindowResizing);
	DispatchEvent(&eventDispatcher, FE_Event_WindowClose, OnWindowClose);

	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		if (!event.isHandled)
		{
			g_fe_App.layerStack.dataPtr[i]->OnUpdateLayerEvent(&event);
		}
		else
		{
			break;
		}
	}
}

BOOL OnWindowResizing(FE_EventData* eventData)
{
	if(eventData->windowData->w == 0 || eventData->windowData->h == 0)
	{
		eventData->windowData->isMinimized = TRUE;
		return FALSE;
	}

	eventData->windowData->isMinimized = FALSE;
	return TRUE;
}

BOOL OnWindowClose(FE_EventData* eventData)
{
	g_IsAppRunning = FALSE;
	return FALSE;
}

void PullWindowEvent()
{
	g_Window_API.PollEvent();
	
}

void Render()
{
	
	
}

void ShutdownApp()
{
	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		PopLayerStack(&g_fe_App.layerStack);
	}
}

void QuitApp()
{
	g_IsAppRunning = FALSE;
}

const FE_App* GetApp()
{
	return &g_fe_App;
}