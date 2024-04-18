#include "fepch.h"
#include "Platform/Windows/SDL/SDLWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include <SDL.h>

BOOL CreateSDLWindow_impl()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	g_WindowData.nativeWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,//TODO: wtf is hardcode??
		SDL_WINDOW_BORDERLESS
	);

	if (!g_WindowData.nativeWindow)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}

	return TRUE;
}

void SDLPollEvent_impl()
{
	SDL_Event event;
	SDL_PollEvent(&event);
}

void SDLDestroyWindow_impl(WindowData* windowData)
{
	SDL_DestroyWindow(windowData->nativeWindow);
	SDL_Quit();
}
