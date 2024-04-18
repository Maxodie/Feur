#include "fepch.h"
#include "Feur/Core/Input/Input.h"

#include "Platform/Windows/SDL/SDLWindowsInput.h"
#include "Platform/Windows/GLFW/GLFWWindowsInput.h"
#include "Feur/Core/Window/Window.h"

typedef enum { Pressed, Repeat, Released }keySate;

void InitInputAPI()
{
	switch (g_Window_API.API_Type)
	{

	case WINDOW_API_SDL:
		g_Input_API.GetKeyPressed = SDLWindowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = SDLWindowsIsInputDown_impl;
		break;

	case WINDOW_API_GLFW:
		g_Input_API.GetKeyPressed = GLFWWindowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = GLFWWindowsIsInputDown_impl;
		break;

	default:
		break;
	}
}

BOOL IsInputPressed(FE_KeyCode key_code)
{
	return (*g_Input_API.GetKeyPressed)(key_code);
}