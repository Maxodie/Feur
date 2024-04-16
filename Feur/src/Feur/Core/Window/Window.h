#pragma once

typedef enum { WINDOW_API_SDL, WINDOW_API_GLFW } Window_API_Type;

typedef struct WindowData
{
	void* nativeWindow;
} WindowData;

typedef struct Window_API
{
	Window_API_Type API_Type;
	BOOL(*CreateWindow)();//give the windowData for the creation ?
} Window_API;


Window_API g_Window_API; // set sdl directly here because there is only sdl so ¯\_(ツ)_/¯
WindowData g_WindowData;

void InitWindow();
BOOL CreateWindow();