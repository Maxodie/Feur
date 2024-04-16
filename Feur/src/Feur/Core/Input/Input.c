#include "fepch.h"
#include "Feur/Core/Input/Input.h"

#include "Platform/Windows/SDL/WindowsInput.h"
#include "Feur/Core/Window/Window.h"

typedef enum { Pressed, Repeat, Released }keySate;

void InitInputAPI()
{
	switch (window_API.API_Type)
	{
	case API_SDL:
		g_Input_API.GetKeyPressed = windowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = windowsIsInputDown_impl;
		break;
	default:
		break;
	}
}

BOOL IsInputPressed(uint8_t key_code)
{
	return (*g_Input_API.GetKeyPressed)(key_code);
}