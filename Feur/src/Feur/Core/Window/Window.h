#pragma once

typedef enum { API_SDL } Window_API_Type;

typedef struct 
{
	void* nativeWindow;
} WindowData;

typedef struct
{
	Window_API_Type API_Type;
	BOOL(*CreateWindow)();//give the windowData for the creation ?
} Window_API;


Window_API window_API = { .API_Type = API_SDL }; // set sdl directly here because there is only sdl so ¯\_(ツ)_ / ¯
WindowData g_WindowData = { 0 };
void InitWindow();
BOOL CreateWindow();