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
	//ecs test
	g_fe_App.cam3DComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompCamera3D));
	g_fe_App.meshComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompMesh));

	g_fe_App.ecsContext.registry = &g_fe_App.ecsRegistry;

	//FE_EntityID newEntity = FE_EntityCreate(&g_fe_App.ecsRegistry);
	//FE_EntityID newEntity1 = FE_EntityCreate(&g_fe_App.ecsRegistry);
	//FE_EntityID newEntity2 = FE_EntityCreate(&g_fe_App.ecsRegistry);
	//FE_EntityID newEntity3 = FE_EntityCreate(&g_fe_App.ecsRegistry);
	//FE_EntityID newEntity4 = FE_EntityCreate(&g_fe_App.ecsRegistry);

	//FE_CORE_LOG_DEBUG("attach e0 : cam");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));

	//FE_CORE_LOG_DEBUG("attach e1 : cam");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));

	//FE_EntityComponentTypeID newComp = FE_EntityCreateComponentType(&g_fe_App.ecsRegistry, sizeof(FE_CompTransform3D));

	//FE_CORE_LOG_DEBUG("component tra capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, newComp)->count, sizeof(FE_CompTransform3D));
	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("attach e2 : cam");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity1, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("attach e3 : cam");
	//FE_Camera3D* camComp = FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity2, g_fe_App.cam3DComp);
	//camComp->position.x = 5.f;

	//FE_CORE_LOG_DEBUG("%f", ((FE_Camera3D*)FE_EntityComponentQueryFromID(&g_fe_App.ecsRegistry, newEntity2, g_fe_App.cam3DComp))->position.x);
	//FE_CORE_LOG_DEBUG("component tra capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, newComp)->count, sizeof(FE_CompTransform3D));
	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("attach e1 : tra");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity, newComp);

	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));

	//FE_CORE_LOG_DEBUG("component tra capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, newComp)->count, sizeof(FE_CompTransform3D));

	//FE_CORE_LOG_DEBUG("attach e0 : tra");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp);

	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("detach e0 : cam");
	//FE_EntityDetachComp(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("attach e0 : cam");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("attach e1 : cam");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("destroy e1");
	//FE_EntityDestroy(&g_fe_App.ecsRegistry, newEntity);

	//FE_CORE_LOG_DEBUG("create e1");
	//newEntity = FE_EntityCreate(&g_fe_App.ecsRegistry);

	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));

	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("attach e1 : tra");
	//FE_EntityAttachComp(&g_fe_App.ecsRegistry, newEntity, newComp);

	//FE_EntityPrintEntityCompFlags(&g_fe_App.ecsRegistry, newEntity);
	//FE_CORE_LOG_DEBUG("e0 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e1 : cam %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, g_fe_App.cam3DComp));
	//FE_CORE_LOG_DEBUG("e0 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, g_fe_App.camEntity, newComp));
	//FE_CORE_LOG_DEBUG("e1 : tra %d", FE_EntityHasComponent(&g_fe_App.ecsRegistry, newEntity, newComp));

	//FE_CORE_LOG_DEBUG("component tra capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, newComp)->count, sizeof(FE_CompTransform3D));
	//FE_CORE_LOG_DEBUG("component cam capacity : %lld     single dataSize : %lld", FE_EntityComponentListQueryFromID(&g_fe_App.ecsRegistry, g_fe_App.cam3DComp)->count, sizeof(FE_Camera3D));
	////ecs test

	g_fe_App.endTime = clock();
	double deltaTime;

	while (g_IsAppRunning)
	{
		deltaTime = GetDeltaTime();

		g_fe_App.ecsContext.dt = deltaTime;

		PullWindowEvent();
		AppUpdate(deltaTime);

		ConsumeDeltaTime(deltaTime);
	}

	ShutdownApp();
}

void FE_DECL StartApp()
{
	FE_MemoryGeneralInit(FE_MEMORY_DEFAULT_STACK_ALLOCATION_SIZE);
	g_fe_App.targetFps = 1000 / 165;
	InitRendererAPISelection(&g_fe_App.rendererData);
	LoadWindow();
	FE_InitInputAPI();
	FE_LayerStackInit(&g_fe_App.layerStack);

	if (!InitRenderer(&g_fe_App.rendererData))
	{
		FE_CORE_LOG_ERROR("failed to initialize the renderer");
	}

	FE_Renderer2DInit();

	NuklearGUIInterfaceInit(&g_fe_App.guiInterface);
	g_fe_App.guiInterface.Init(&g_fe_App.guiInterface);

	FE_EntityCreateRegistry(&g_fe_App.ecsRegistry);
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

	FE_ECSComputeSystem(FE_ECSComputeDraw, g_fe_App.meshComp, &g_fe_App.ecsContext);

	g_fe_App.guiInterface.OnBeginRender(&g_fe_App.guiInterface);

	for (SizeT i = 0; i < FE_LayerStackGetCount(&g_fe_App.layerStack); i++)
	{
		g_fe_App.layerStack.stackedlayers.data[i]->OnNuklearRender(&g_fe_App.guiInterface, g_fe_App.layerStack.stackedlayers.data[i]);
	}


	g_fe_App.guiInterface.OnEndRender(&g_fe_App.guiInterface);

	RenderCommandEndRendering();
	RenderCommandFrameCommandListEnd();
	RenderCommandFrameSubmit();
	RenderCommandFramePresent();
	RenderCommandWaitIdle();

	FE_Renderer2DReset();


	GetWindowAPI()->Update(&g_fe_App.windowData);
}


void FE_DECL AddLayerApp(Layer* newLayer)
{
	FE_LayerStackPush(&g_fe_App.layerStack, newLayer);
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
	g_fe_App.guiInterface.OnWindowResize(eventData->windowData->w, eventData->windowData->h);

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
	FE_EntityDestroyRegistry(&g_fe_App.ecsRegistry);

	g_fe_App.guiInterface.Shutdown();

	FE_LayerStackClear(&g_fe_App.layerStack);

	FE_Renderer2DShutdown();
	FE_CORE_LOG_SUCCESS("2D Renderer shuted down");
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