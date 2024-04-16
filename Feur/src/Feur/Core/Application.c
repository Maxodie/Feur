#include "fepch.h"
#include "Feur/Core/Application.h"

//TEMp include
#include <SDL.h>
#include "Feur/Core/Window/Window.h"//need to stock the window in app data or something
#include "Feur/Core/Input/Input.h"

BOOL g_IsAppRunning = TRUE;
//Temp window
SDL_Renderer* g_Renderer;

void Start();
BOOL InitWindowTemp();
void LoadWindow();
void PullWindowEvent();
void Render();


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
	InitWindowTemp();
}

void LoadWindow()
{
	InitWindow();
	g_Window_API.CreateWindow();
}

BOOL InitWindowTemp()
{
	g_Renderer = SDL_CreateRenderer(g_WindowData.nativeWindow, -1, 0);

	if (!g_Renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}
	//
	return TRUE;
}

void PullWindowEvent()
{
	SDL_Event event;
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
	}
}

void Render()
{
	SDL_SetRenderDrawColor(g_Renderer, 50, 50, 50, 255);
	SDL_RenderClear(g_Renderer);

	//TODO : start drawing GameObjects
	SDL_RenderPresent(g_Renderer);
}