#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include <GLFW/glfw3.h>

BOOL CreateSDLWindow_impl()
{
	g_WindowData.nativeWindow = glfwCreateWindow(
		800, 600,//TODO: wtf is hardcode??
		NULL, NULL, NULL
	);

	if (!g_WindowData.nativeWindow)
	{
		fprintf(stderr, "Error creating SDL Window.\n");
		return FALSE;
	}

	return TRUE;
}