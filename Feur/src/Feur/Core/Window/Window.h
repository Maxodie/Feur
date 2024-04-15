#pragma once

typedef enum { API_SDL }Input_API_Type;//TODO : put this as window api and put it in window

typedef struct
{
	bool (*CreateWindow)(uint8_t);
	bool (*GetKeyDown)(uint8_t);
} Window_API;

typedef struct {
	Input_API_Type windowAPI;
} WindowData;

WindowData g_WindowData;

void InitWindow();
void CreateWindow();