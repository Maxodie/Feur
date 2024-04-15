/*#include <stdio.h>
#include <SDL.h>
#include <inttypes.h>
#include "constant.h"
#include "game.h"


#include "Input/Input.h"*/
#include "fepch.h"
/*
int last_frame_time = 0;

struct Test {
	float x, y;
	float w, h;
};

struct Test test;

int main(int argc, char* argv[])
{
	g_IsRunning = initialize_window();

	setup();

	while (g_IsRunning)
	{
		process_event_input();
		update();
		render();
	}

	destroy_window();

	return 0;
}

int initialize_window(void) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		fprintf(stderr, "Error initializing SDl.\n");
		return FALSE;
	}

	g_Window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);

	if (!g_Window)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}

	g_Renderer = SDL_CreateRenderer(g_Window, -1, 0);

	if (!g_Renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void process_event_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			g_IsRunning = FALSE;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_IsRunning = FALSE;
			}
			break;

		default:
			break;
	}
}

void setup()
{
	test.x = 20;
	test.y = 20;
	test.h = 100;
	test.w = 15;
}

void update()
{
	update_delta_time();
	process_update_input();
	//fps capping
	/*int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	if (time_to_wait > 0 && time_to_wait >= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}

	
}

void update_delta_time()
{
	g_DeltaTime = (SDL_GetTicks() - last_frame_time) / 1000.f;

	last_frame_time = SDL_GetTicks();
}

void process_update_input()
{
	const uint8_t* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_DOWN])
	{

		test.y += 20 * g_DeltaTime;
	}

	if (keystates[SDL_SCANCODE_RIGHT])
	{

		test.x += 20 * g_DeltaTime;
	}
}

void render()
{
	SDL_SetRenderDrawColor(g_Renderer, 50, 50, 50, 255);
	SDL_RenderClear(g_Renderer);

	//TODO : start drawing GameObjects
	SDL_Rect rect = { (int)test.x, (int)test.y, (int)test.w, (int)test.h };
	SDL_SetRenderDrawColor(g_Renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(g_Renderer, &rect);
	SDL_RenderPresent(g_Renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(g_Renderer);
	SDL_DestroyWindow(g_Window);
	SDL_Quit();
}*/