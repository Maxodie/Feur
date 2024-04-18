#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsInput.h"
#include "Feur/Core/Window/Window.h"
#include <GLFW/glfw3.h>

BOOL GLFWWindowsIsInputPressed_impl(FE_KeyCode key_code)
{
	//assert(false,"\n----------\nERROR : GLFW Get Key for windows not implemented yet.\n----------\n");
	assert(FALSE);
	return FALSE;

	/*const int sdlKeycode = SDL_GetKeyFromScancode(key_code);
	const char* keyName = SDL_GetKeyName(sdlKeycode);

	const int sdlScancode = SDL_GetScancodeFromKey(sdlKeycode);//FE keycodes are based on SDL that why i use SDL to easily convert
	const int state = glfwGetKey(g_WindowData.nativeWindow, sdlScancode);*/

//	return state == GLFW_PRESS;
}

BOOL GLFWWindowsIsInputDown_impl(FE_KeyCode key_code)
{
	//assert(false,"\n----------\nERROR : GLFW Get Key Down for windows not implemented yet.\n----------\n");
	assert(FALSE);
	return FALSE;
}