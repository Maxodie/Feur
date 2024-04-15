#pragma once
#include <SDL.h>
int g_IsRunning = FALSE;
SDL_Window* g_Window = NULL;
SDL_Renderer* g_Renderer = NULL;

float g_DeltaTime = 0.f;

int initialize_window(void);
void setup();
void process_event_input();

void update();
void update_delta_time();
void process_update_input();
void render();
void destroy_window();