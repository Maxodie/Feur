#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Event/Event.h"
#include "Feur/Core/Input/Input.h"
#include "Feur/Renderer/RenderCommand.h"
#include "Feur/Nuklear/NuklearLayer.h"

static FE_App g_fe_App;

static Bool g_IsAppRunning = TRUE;

Layer nuklearGUILayer;

void FE_DECL StartApp_impl()
{
	StartApp();
}

void FE_DECL RunApp_impl()
{
	g_fe_App.endTime = clock();
	double deltaTime;

	while (g_IsAppRunning)
	{
		deltaTime = GetDeltaTime();

		PullWindowEvent();
		AppUpdate(deltaTime);

		ConsumeDeltaTime(deltaTime);
	}

	ShutdownApp();
}

void FE_DECL StartApp()
{
	FE_MemoryGeneralInit(FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE);
	InitRendererAPISelection(&g_fe_App.rendererAPIData);
	LoadWindow();
	FE_InitInputAPI();
	FE_LayerStackInit(&g_fe_App.layerStack);

	if (!InitRenderer(&g_fe_App.rendererAPIData))
	{
		FE_CORE_LOG_ERROR("failed to initialize the renderer");
	}

	FE_Renderer2DInit();

	nuklearGUILayer = CreateNewNuklearGUILayer("NuklearLayer");
	AddLayerApp(&nuklearGUILayer);

	g_fe_App.targetFps = 1000 / 165;
}

Double GetDeltaTime()
{
	g_fe_App.startTime = clock();
	return ((Double)(g_fe_App.startTime - g_fe_App.endTime)) / CLOCKS_PER_SEC;
}

void ConsumeDeltaTime(Double deltaTime)
{
	g_fe_App.endTime = clock();
	Uint32 elapsedTimeMs = (Uint32)(g_fe_App.endTime - g_fe_App.startTime);
	//FE_CORE_LOG_DEBUG("ms : %d", elapsedTimeMs);

	if (g_fe_App.targetFps > elapsedTimeMs)
	{
		Uint32 msToConsume = (Uint32)ILDA_clamp(g_fe_App.targetFps - elapsedTimeMs, 0, 1000);
#ifdef FE_PLATFORM_WINDOWS
		Sleep((DWORD)msToConsume);
#elif defined(FE_PLATFORM_LINUX)
		usleep((msToConsume % 1000) * 1000)
#endif
	}

}

void FE_DECL AppPrepareRender()
{
	RenderCommandFramePrepare();
	RenderCommandFrameCommandListBegin();
	RenderCommandBeginRendering(&g_fe_App.rendererAPIData.defaultClearColor);

	RenderCommandSetRendererViewport(0, 0, g_fe_App.windowData.w, g_fe_App.windowData.h, 0, 1);
	RenderCommandSetScissor(g_fe_App.windowData.w, g_fe_App.windowData.h);
	RenderCommandBindPipeline();
}

void FE_DECL AppUpdate(Double deltaTime)
{
	AppPrepareRender();
	
	for (int i = 0; i < g_fe_App.layerStack.stackedlayers.impl.count; i++)
	{
		g_fe_App.layerStack.stackedlayers.data[i]->OnUpdate(deltaTime);
	}

	RenderCommandEndRendering();
	RenderCommandFrameCommandListEnd();
	RenderCommandFrameSubmit();
	RenderCommandFramePresent();
	RenderCommandWaitIdle();

	FE_Renderer2DReset();

	Layer* layer;
	for (SizeT i = 0; i < FE_LayerStackGetCount(&g_fe_App.layerStack); i++)
	{
		layer = g_fe_App.layerStack.stackedlayers.data[i];
		layer->OnNuklearRender(layer);
	}

	GetWindowAPI()->Update(&g_fe_App.windowData);
}


void FE_DECL AddLayerApp(Layer* newLayer)
{
	FE_LayerStackPush(&g_fe_App.layerStack, newLayer);
	newLayer->OnAttach(newLayer);
}

void FE_DECL InsertLayerApp(Layer* newLayer, Uint32 position)
{
	FE_LayerStackInsert(&g_fe_App.layerStack, newLayer, position);
}

void FE_DECL PopLayerApp()
{
	FE_LayerStackPop(&g_fe_App.layerStack);
}

void FE_DECL LoadWindow()
{
	InitWindowAPI();
	CreateAppWindow(&g_fe_App.windowData);
	g_fe_App.windowData.graphicsContext.Init(&g_fe_App.windowData);

	g_fe_App.windowData.EventCallback = AppOnEvent;
}

void FE_DECL AppOnEvent(FE_Event event)
{
	FE_EventDispatcher eventDispatcher = { .eventType = event.eventType, .event = event };
	DispatchEvent(&eventDispatcher, FE_Event_WindowResize, OnWindowResizing);
	DispatchEvent(&eventDispatcher, FE_Event_WindowClose, OnWindowClose);

	for (SizeT i = 0; i < FE_LayerStackGetCount(&g_fe_App.layerStack); i++)
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

Bool FE_DECL OnWindowResizing(FE_EventData* eventData)
{
	if(eventData->windowData->w == 0 || eventData->windowData->h == 0)
	{
		eventData->windowData->isMinimized = TRUE;
		return FALSE;
	}

	eventData->windowData->isMinimized = FALSE;
	RendererOnWindowResize(eventData->windowData->w, eventData->windowData->h);//not frame limited so it can use a lot of GPU performence now
	return TRUE;
}

Bool FE_DECL OnWindowClose(FE_EventData* eventData)
{
	g_IsAppRunning = FALSE;
	return FALSE;
}

void FE_DECL PullWindowEvent()
{
	GetWindowAPI()->PollEvent();
}

void FE_DECL ShutdownApp()
{
	FE_LayerStackClear(&g_fe_App.layerStack);

	FE_Renderer2DShutdown();
	FE_CORE_LOG_SUCCESS("2D Renderer shuted down");
	RendererShutdown(&g_fe_App.rendererAPIData);
	FE_CORE_LOG_SUCCESS("Renderer shuted down");
	GetWindowAPI()->DestroyWindow(&g_fe_App.windowData);
	FE_CORE_LOG_SUCCESS("Window destroyed");

	FE_ListPrintReport();

	FE_MemoryGeneralShutdown();
	FE_CORE_LOG_SUCCESS("Memory freed");
	FE_CORE_LOG_SUCCESS("Application closed");

//#include "windows.h"
//#define _CRTDBG_MAP_ALLOC
//#define _CRTDBG_DELAY_FREE_MEM_DF 
//#include <crtdbg.h>
// 	   #include <crtdbg.h>
//	_CrtMemState sOld;
//	_CrtMemState sNew;
//	_CrtMemState sDiff;
// 	   _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
//	_CrtMemCheckpoint(&sOld); //take a snapshot
//	_CrtMemCheckpoint(&sNew);
//	if (_CrtMemDifference(&sDiff, &sOld, &sNew))
//	{
//		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
//		_CrtMemDumpStatistics(&sDiff);
//		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
//		_CrtMemDumpAllObjectsSince(&sOld);
//		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
//		_CrtDumpMemoryLeaks();
//	}
}

void FE_DECL QuitApp()
{
	g_IsAppRunning = FALSE;
}

const FE_App* FE_DECL GetApp()
{
	return &g_fe_App;
}