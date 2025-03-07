#include "fepch.h"
#include "Feur/Core/Input/Input.h"
#include "Feur/Core/Input/KeyCode.h"

#include "Platform/Window/SDL/SDLWindowsInput.h"
#include "Platform/Window/GLFW/GLFWWindowsInput.h"
#include "Feur/Core/Window/Window.h"

typedef enum keySate { Pressed, Repeat, Released } keySate;

Input_API g_Input_API;

void FE_DECL FE_InitInputAPI()
{
	switch (GetWindowAPI()->API_Type)
	{

	case FE_WINDOW_API_SDL:
		g_Input_API.GetKeyPressed = SDLWindowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = SDLWindowsIsInputDown_impl;
		break;

	case FE_WINDOW_API_GLFW:
		g_Input_API.GetKeyPressed = GLFWWindowsIsInputPressed_impl;
		g_Input_API.GetKeyDown = GLFWWindowsIsInputDown_impl;
		break;

	default:
		break;
	}
}

Bool FE_DECL FE_IsInputPressed(const FE_KeyCode key_code)
{
	return g_Input_API.GetKeyPressed(key_code);
}

const ILDA_vector2d* GetCursorPosition()
{
	return &GetApp()->windowData.windowMousePos;
}
