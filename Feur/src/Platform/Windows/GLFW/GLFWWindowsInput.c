#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsInput.h"
#include "Feur/Core/Window/Window.h"
#include <GLFW/glfw3.h>

BOOL GLFWWindowsIsInputPressed_impl(Uint8 key_code)
{
	int state = glfwGetKey(g_WindowData.nativeWindow, GLFW_KEY_E);
}

BOOL GLFWWindowsIsInputDown_impl(Uint8 key_code)
{
	//assert(false,"\n----------\nERROR : Get Key Down for windows not implemented yet.\n----------\n");
	assert(FALSE);
	return FALSE;
}
