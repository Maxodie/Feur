#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Event/Event.h"
#include "Feur/Core/Input/Input.h"
#include "Feur/Renderer/RenderCommand.h"
#include "Feur/Nuklear/NuklearLayer.h"

static FE_App g_fe_App;

static Bool g_IsAppRunning = TRUE;

Layer nuklearGUILayer;

void FE_API StartApp_impl()
{
	StartApp();
}

void FE_API RunApp_impl()
{
	while (g_IsAppRunning)
	{
		PullWindowEvent();
		AppUpdate();
		Render();
	}

	ShutdownApp();
}


void FE_API AppUpdate()
{
	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		g_fe_App.layerStack.stackedlayers.data[i]->OnUpdate();
	}
}


void FE_API StartApp()
{
	FE_MemoryGeneralInit(FE_MEMORY_SMALL_POOL_ALLOCATION_SIZE);
	InitRendererAPISelection();
	LoadWindow();
	InitInputAPI();
	InitLayerStack(&g_fe_App.layerStack);

	if (!InitRenderer(&g_fe_App.rendererAPIData))
	{
		FE_CORE_LOG_ERROR("Application.c : RenderCommandInit failed !");
	}

	nuklearGUILayer = CreateNewNuklearGUILayer("NuklearLayer");
	AddLayerApp(&nuklearGUILayer);
}

void FE_API AddLayerApp(Layer* newLayer)
{
	PushLayerStack(&g_fe_App.layerStack, newLayer);
	newLayer->OnAttach(newLayer);
}

void FE_API InsertLayerApp(Layer* newLayer, Uint32 position)
{
	InsertLayerStack(&g_fe_App.layerStack, newLayer, position);
}

void FE_API PopLayerApp()
{
	PopLayerStack(&g_fe_App.layerStack);
}

void FE_API LoadWindow()
{
	InitWindowAPI();
	CreateAppWindow(&g_fe_App.windowData);
	g_fe_App.windowData.graphicsContext.Init(&g_fe_App.windowData);

	g_fe_App.windowData.EventCallback = AppOnEvent;
}

void FE_API AppOnEvent(FE_Event event)
{
	FE_EventDispatcher eventDispatcher = { .eventType = event.eventType, .event = event };
	DispatchEvent(&eventDispatcher, FE_Event_WindowResize, OnWindowResizing);
	DispatchEvent(&eventDispatcher, FE_Event_WindowClose, OnWindowClose);

	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		if (!event.isHandled)
		{
			g_fe_App.layerStack.stackedlayers.data[i]->OnUpdateLayerEvent(&event);
		}
		else
		{
			break;
		}
	}
}

Bool FE_API OnWindowResizing(FE_EventData* eventData)
{
	if(eventData->windowData->w == 0 || eventData->windowData->h == 0)
	{
		eventData->windowData->isMinimized = TRUE;
		return FALSE;
	}

	eventData->windowData->isMinimized = FALSE;
	RendererOnWindowResize(eventData->windowData->w, eventData->windowData->h);
	return TRUE;
}

Bool FE_API OnWindowClose(FE_EventData* eventData)
{
	g_IsAppRunning = FALSE;
	return FALSE;
}

void FE_API PullWindowEvent()
{
	GetWindowAPI()->PollEvent();
}

void FE_API Render()
{
	RenderCommandClearScreenColor();
	RenderCommandClear();

	Layer* layer;
	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		layer = g_fe_App.layerStack.stackedlayers.data[i];
		layer->OnRender(layer);
	}

	GetWindowAPI()->Update(&g_fe_App.windowData);
}

void FE_API ShutdownApp()
{
	for (int i = 0; i < g_fe_App.layerStack.count; i++)
	{
		PopLayerStack(&g_fe_App.layerStack);
	}

	RendererShutdown(&g_fe_App.rendererAPIData);
	GetWindowAPI()->DestroyWindow(&g_fe_App.windowData);
}

void FE_API QuitApp()
{
	g_IsAppRunning = FALSE;
}

const FE_API FE_App* GetApp()
{
	return &g_fe_App;
}