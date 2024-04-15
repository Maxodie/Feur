#pragma once

typedef enum { API_SDL }Window_API;

typedef struct
{
	bool (*CreateWindow)();
} Window_API;

typedef struct {
	Window_API windowAPI;
} WindowData;

WindowData g_WindowData;

void InitWindow();
void CreateWindow();