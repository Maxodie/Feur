#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include <GLFW/glfw3.h>

BOOL CreateGLFWWindow_impl()
{
	glfwInit();
	g_WindowData.nativeWindow = glfwCreateWindow(
		800, 600,//TODO: wtf is hardcode??
		"window", NULL, NULL
	);

	if (!g_WindowData.nativeWindow)
	{
		fprintf(stderr, "Error creating GLFW Window.\n");
		return FALSE;
	}

	return TRUE;
}

void GLFWPollEvent_impl()
{
	glfwPollEvents();
}

void GLFWDestroyWindow_impl(WindowData* windowData)
{
	glfwDestroyWindow(windowData->nativeWindow);
	glfwTerminate();
}
