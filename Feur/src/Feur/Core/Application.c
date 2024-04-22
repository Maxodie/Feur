#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Core/Event/Event.h"
//TEMp include
#include <SDL.h>
#include <GLFW/glfw3.h>
#include "Feur/Core/Input/Input.h"

BOOL g_IsAppRunning = TRUE;
//Temp window
SDL_Renderer* g_Renderer;

void Start();
extern void Update();
BOOL InitWindowTemp();
void LoadWindow();
void PullWindowEvent();
void Render();
void AppOnEvent(FE_Event event);
BOOL OnWindowResizing(FE_EventData* windowResizeEvent);
BOOL OnWindowClose(FE_EventData* windowResizeEvent);

void RunApp_impl()
{
	Start();

	while (g_IsAppRunning)
	{
		PullWindowEvent();
		Update();
		Render();
	}
}
void Start()
{
	LoadWindow();
	InitInputAPI();
	//InitWindowTemp();
}

void LoadWindow()
{
	InitWindow();
	g_Window_API.CreateWindow(&g_fe_App.windowData);

	g_fe_App.windowData.EventCallback = AppOnEvent;
}

BOOL InitWindowTemp()
{
	g_Renderer = SDL_CreateRenderer(g_fe_App.windowData.nativeWindow, -1, 0);

	if (!g_Renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void AppOnEvent(FE_Event event)
{
	FE_EventDispatcher eventDispatcher = { .eventType = event.eventType, .event = event };//put function in dispatchEvent function
	DispatchEvent(&eventDispatcher, FE_Event_WindowResize, OnWindowResizing);
	DispatchEvent(&eventDispatcher, FE_Event_WindowClose, OnWindowClose);

	/*switch (eventType)
	{
	case FE_Event_WindowResize:

		break;
	default:
		break;
	}*/

	//TODO layer system with event handling
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
	//glfwPollEvents();
	/*SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		printf("quit");
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_Quit();
		}
		break;

	default:
		break;
	}*/
}

void Render()
{
	
	/*SDL_SetRenderDrawColor(g_Renderer, 50, 50, 50, 255);
	SDL_RenderClear(g_Renderer);

	//TODO : start drawing GameObjects
	SDL_RenderPresent(g_Renderer);*/
}