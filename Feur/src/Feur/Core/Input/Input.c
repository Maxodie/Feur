#include "fepch.h"

#include "Platform/Windows/SDL/WindowsInput.h"
#include "Input.h"
#include <SDL.h>

typedef enum { Pressed, Repeat, Released }keySate;
typedef enum { API_SDL }Input_API_Type;//TODO : put this as window api and put it in window

g_Input_API_Type = API_SDL;



void InitInputAPI()
{
	switch (g_Input_API_Type)
	{
	case API_SDL:
		g_Input_API.GetKeyPressed = windowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = windowsIsInputDown_impl;
		break;
	default:
		break;
	}
}

bool IsInputPressed(uint8_t key_code)
{
	return (*g_Input_API.GetKeyPressed)(key_code);
}