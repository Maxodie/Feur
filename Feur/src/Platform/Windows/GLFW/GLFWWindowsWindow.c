#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include <GLFW/glfw3.h>

BOOL CreateGLFWWindow_impl(WindowData* windowData)
{
	glfwInit();

	windowData->w = 800;
	windowData->h = 600;

	windowData->nativeWindow = glfwCreateWindow(
		windowData->w, windowData->h,
		"window", NULL, NULL
	);

	if (!windowData->nativeWindow)
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
