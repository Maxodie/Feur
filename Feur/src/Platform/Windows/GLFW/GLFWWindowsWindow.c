#include "fepch.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include "Feur/Core/Event/Event.h"
#include <GLFW/glfw3.h>

void SetWindowSizeCallback(GLFWwindow* window, int width, int height);

static void GLFWErrorCallback(int error, const char* description);


BOOL CreateGLFWWindow_impl(WindowData* windowData)
{
	int sucess = glfwInit();

	windowData->w = 800;
	windowData->h = 600;
	GLFWwindow* glfwWindow = glfwCreateWindow(
		windowData->w, windowData->h,
		"window", NULL, NULL
	);

	if (!glfwWindow)
	{
		fprintf(stderr, "Error creating GLFW Window.\n");
		return FALSE;
	}

	glfwSetErrorCallback(GLFWErrorCallback);

	glfwSetWindowUserPointer(glfwWindow, windowData);

	glfwSetWindowSizeCallback(glfwWindow, SetWindowSizeCallback);

	windowData->nativeWindow = glfwWindow;
	return TRUE;
}

void GLFWErrorCallback(int error, const char* description)
{
	FE_CORE_LOG_ERROR("GLFW Error ({%d}): {%s}", error, description);
}

void SetWindowSizeCallback(GLFWwindow * window, int width, int height)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .w = width, .h = height };
	FE_Event event = {.eventCategory = FE_EventCategory_Application, .eventType = FE_Event_WindowResize, .eventData = eventData };

	data->w = width;
	data->h = height;

	data->EventCallback(event);
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
