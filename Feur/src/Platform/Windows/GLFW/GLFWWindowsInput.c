#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsInput.h"
#include "Feur/Core/Application.h"
#include <GLFW/glfw3.h>

Bool FE_API GLFWWindowsIsInputPressed_impl(const FE_KeyCode key_code)
{
	const int state = glfwGetKey(GetApp()->windowData.nativeWindow, key_code);
	//assert(false,"\n----------\nERROR : GLFW Get Key for windows not implemented yet.\n----------\n");

	return state == GLFW_PRESS;

	/*const int sdlKeycode = SDL_GetKeyFromScancode(key_code);
	const char* keyName = SDL_GetKeyName(sdlKeycode);

	const int sdlScancode = SDL_GetScancodeFromKey(sdlKeycode);//FE keycodes are based on SDL that why i use SDL to easily convert
	const int state = glfwGetKey(g_WindowData.nativeWindow, sdlScancode);*

//	return state == GLFW_PRESS;*/
}

Bool FE_API GLFWWindowsIsInputDown_impl(const FE_KeyCode key_code)
{
	//assert(false,"\n----------\nERROR : GLFW Get Key Down for windows not implemented yet.\n----------\n");
	FE_CORE_ASSERT(FALSE, "ERROR : GLFW Get Key Down for windows not implemented yet.");
	return FALSE;
}