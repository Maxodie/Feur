#include "fepch.h"
#include "Feur/Core/Application.h"
#include "Feur/Core/Input/Input.h"

//TEMp include
#include <SDL.h>

bool g_IsAppRunning = true;
//Temp window
SDL_Window* g_Window;
SDL_Renderer* g_Renderer;

void Start();
bool InitWindow();
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
	InitInputAPI();
	InitWindow();
}

bool InitWindow()
{
	

	g_Renderer = SDL_CreateRenderer(g_Window, -1, 0);

	if (!g_Renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return false;
	}
	//
	return true;
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