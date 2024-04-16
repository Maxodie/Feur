#include "fepch.h"
#include "Platform/Windows/SDL/WindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include <SDL.h>

BOOL CreateSDLWindow_impl()
{
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