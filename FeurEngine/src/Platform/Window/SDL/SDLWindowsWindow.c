#include "fepch.h"
#include "Platform/Window/SDL/SDLWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
//#include <SDL.h>

Bool FE_DECL CreateSDLWindow_impl(WindowData* windowData)
{
	/*windowData->w = 800;
	windowData->h = 600;

	SDL_Init(SDL_INIT_EVERYTHING);
	windowData->nativeWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowData->w, windowData->h,
		SDL_WINDOW_BORDERLESS
	);

	if (!windowData->nativeWindow)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}*/

	return TRUE;
}

void FE_DECL SDLPollEvent_impl()
{
	/*SDL_Event event;
	SDL_PollEvent(&event);*/
}

void FE_DECL SDLDestroyWindow_impl(WindowData* windowData)
{
	/*SDL_DestroyWindow(windowData->nativeWindow);
	SDL_Quit();*/
}
