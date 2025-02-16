#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Event/Event.h"
#include "Feur/Core/Input/Input.h"
#include "Feur/Renderer/RenderCommand.h"
#include "Feur/Nuklear/NuklearLayer.h"

#include "Feur/Core/Utils/ECS/ECSSystems.h"

static FE_App g_fe_App;

static Bool g_IsAppRunning = TRUE;

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

		g_fe_App.ecsContext.dt = deltaTime;

		PullWindowEvent();

		AppUpdate(deltaTime);

		FE_EventPollTask(&g_fe_App.eventRegistry);
		ConsumeDeltaTime(deltaTime);
	}

	ShutdownApp();
}

void FE_DECL AppInitECS()
{
	FE_EntityCreateRegistry(&g_fe_App.ecsRegistry);

	g_fe_App.cam3DComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompCamera3D));
	g_fe_App.modelComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompModel));
	g_fe_App.tr3DComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompTransform3D));

	g_fe_App.ecsContext.registry = &g_fe_App.ecsRegistry;
}

void FE_DECL StartApp()
{
	FE_MemoryGeneralInit(FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE);
	g_fe_App.targetFps = 1000 / 165;
	InitRendererAPISelection(&g_fe_App.rendererData);
	FE_EventSystemInit(&g_fe_App.eventRegistry);

	LoadWindow();
	FE_InitInputAPI();

	if (!InitRenderer(&g_fe_App.rendererData))
	{
		FE_CORE_LOG_ERROR("failed to initialize the renderer");
	}

	FE_Renderer3DInit();
	FE_Renderer2DInit();

	NuklearGUIInterfaceInit(&g_fe_App.guiInterface);
	g_fe_App.guiInterface.Init(&g_fe_App.guiInterface);

	AppInitECS();

	FE_LayerStackInit(&g_fe_App.layerStack);

	FE_FrameBufferResize(&g_fe_App.frameBuffer, 0, 0, g_fe_App.windowData.w, g_fe_App.windowData.h);
}

Double FE_DECL GetDeltaTime()
{
	g_fe_App.startTime = clock();
	return ((Double)(g_fe_App.startTime - g_fe_App.endTime)) / CLOCKS_PER_SEC;
}

void FE_DECL ConsumeDeltaTime(Double deltaTime)
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
	RenderCommandBeginRendering(&g_fe_App.rendererData.defaultClearColor);

	RenderCommandSetRendererViewport(g_fe_App.frameBuffer.posX, g_fe_App.frameBuffer.posY, g_fe_App.frameBuffer.w, g_fe_App.frameBuffer.h, 0, 1);
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

	NuklearGUIBeginRender();
	RenderCommandSetRendererViewport(0, 0, g_fe_App.windowData.w, g_fe_App.windowData.h, 0, 1);

	for (SizeT i = 0; i < FE_LayerStackGetCount(&g_fe_App.layerStack); i++)
	{
		g_fe_App.layerStack.stackedlayers.data[i]->OnNuklearRender(&g_fe_App.guiInterface, g_fe_App.layerStack.stackedlayers.data[i]);
	}

	NuklearGUIEndRender();

	RenderCommandEndRendering();
	RenderCommandFrameCommandListEnd();
	RenderCommandFrameSubmit();
	RenderCommandFramePresent();
	RenderCommandWaitIdle();

	FE_Renderer2DReset();
	FE_Renderer3DReset();


	GetWindowAPI()->Update(&g_fe_App.windowData);
}

struct FE_LayerStackLambdaTask
{
	Layer* layer;
	Uint32 position;
};

void FE_DECL AddLayerApp(Layer* newLayer)
{
	FE_LayerStackPush(&g_fe_App.layerStack, newLayer);
}

void FE_DECL AddOverlayLayerApp(Layer* newLayer)
{
	FE_LayerStackPushOvelay(&g_fe_App.layerStack, newLayer);
}

void FE_DECL RemoveLayerApp(LayerStack* layerStack, Layer* value)
{
	FE_LayerStackRemoveLayer(layerStack, value);
}

void PopLayerAppTask()
{
	FE_LayerStackPop(&g_fe_App.layerStack);
}

void FE_DECL PopLayerApp()
{
	FE_EventPostTask(&g_fe_App.layerStack, PopLayerAppTask); // task void* parameter
}

void FE_DECL LoadWindow()
{
	InitWindowAPI();
	CreateAppWindow(&g_fe_App.windowData);
	g_fe_App.windowData.graphicsContext.Init(&g_fe_App.windowData);

	FE_EventAttach(&g_fe_App.eventRegistry, FE_Event_WindowClose, OnWindowClose);
	FE_EventAttach(&g_fe_App.eventRegistry, FE_Event_WindowResize, OnWindowResizing);
	g_fe_App.windowData.EventCallback = AppOnEvent;
}

void FE_DECL AppOnEvent(FE_Event event)
{
	FE_EventDispatch(&g_fe_App.eventRegistry, &event);

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
	g_fe_App.guiInterface.OnWindowResize(eventData->windowData->w, eventData->windowData->h);

	FE_ECSComputeSystem(FE_ECSComputeAspectRatioUpdate, g_fe_App.cam3DComp, &g_fe_App.ecsContext);

	return FALSE;
}

Bool FE_DECL OnWindowClose(FE_EventData* eventData)
{
	g_IsAppRunning = FALSE;
	return TRUE;
}

void* FE_DECL GetFrameImageViewApp()
{
	return RenderCommandGetFrameImageView();
}

void FE_DECL PullWindowEvent()
{
	GetWindowAPI()->PollEvent();
}

void FE_DECL ShutdownApp()
{
	FE_LayerStackClear(&g_fe_App.layerStack);

	FE_EntityDestroyRegistry(&g_fe_App.ecsRegistry);

	g_fe_App.guiInterface.Shutdown();
	NuklearGUIInterfaceShutdown(&g_fe_App.guiInterface);

	FE_EventSystemClear(&g_fe_App.eventRegistry);

	FE_Renderer2DShutdown();
	FE_Renderer3DShutdown();
	FE_CORE_LOG_SUCCESS("2D/3D Renderers shuted down");
	RendererShutdown(&g_fe_App.rendererData);
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
