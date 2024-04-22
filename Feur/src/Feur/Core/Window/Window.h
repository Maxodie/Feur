#pragma once

typedef enum { WINDOW_API_SDL, WINDOW_API_GLFW } Window_API_Type;

typedef struct WindowData
{
	int w, h;
	void* nativeWindow;
	void (*EventCallback)(Fe_Event);//bind glfw window events in app start on the onEvent
} WindowData;

typedef struct Window_API
{
	Window_API_Type API_Type;
	BOOL(*CreateWindow)(WindowData*);
	void(*PollEvent)();
	void(*DestroyWindow)(WindowData*);
} Window_API;


Window_API g_Window_API;

void InitWindow();
BOOL CreateWindow(WindowData* windowData);