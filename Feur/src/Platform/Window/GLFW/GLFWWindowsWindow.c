#include "fepch.h"
#include "Platform/Window/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include "Feur/Event/Event.h"
#include <GLFW/glfw3.h>

static void FE_API GLFWErrorCallback(int error, const char* description);
static void FE_API GLFWSetWindowSizeCallback(GLFWwindow* window, int width, int height);
static void FE_API GLFWSetWindowCloseCallback(GLFWwindow* window);
static void FE_API GLFWSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Bool FE_API CreateGLFWWindow_impl(WindowData* windowData)
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
		FE_CORE_LOG_ERROR("Error creating GLFW Window.\n");
		return FALSE;
	}

	FE_CORE_LOG_SUCCESS("   GLFW Window Created");

	glfwSetWindowUserPointer(glfwWindow, windowData);
	
	glfwSetErrorCallback(GLFWErrorCallback); 
	glfwSetWindowSizeCallback(glfwWindow, GLFWSetWindowSizeCallback);
	glfwSetWindowCloseCallback(glfwWindow, GLFWSetWindowCloseCallback);
	///////////////// 
	/*
	glfwSetKeyCallback(glfwWindow, GLFWSetKeyCallback);

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		KeyTypedEvent event(keycode);
		data.EventCallback(event);
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_PRESS: {
			MouseButtonPressedEvent event(button);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			MouseButtonReleasedEvent event(button);
			data.EventCallback(event);
			break;
		}
		}
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.EventCallback(event);
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)xPos, (float)yPos);
		data.EventCallback(event);
		});
	*/ ////////////////////////////////////
	windowData->nativeWindow = glfwWindow;
	return TRUE;
}

static void FE_API GLFWErrorCallback(int error, const char* description)
{
	FE_CORE_LOG_ERROR("GLFW Error ({%d}): {%s}", error, description);
}

static void FE_API GLFWSetWindowSizeCallback(GLFWwindow * window, int width, int height)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .windowData = data };
	FE_Event event = {.eventCategory = FE_EventCategory_Application, .eventType = FE_Event_WindowResize, .eventData = eventData };

	data->w = width;
	data->h = height;

	data->EventCallback(event);
}

static void FE_API GLFWSetWindowCloseCallback(GLFWwindow* window)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .windowData = data };
	FE_Event event = { .eventCategory = FE_EventCategory_Application, .eventType = FE_Event_WindowClose, .eventData = eventData };

	data->EventCallback(event);
}

void FE_API GLFWSetKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	/*switch (action) {
		case GLFW_PRESS: {
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE: {
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT: {
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
	}*/
}


void FE_API GLFWPollEvent_impl()
{
}

void FE_API GLFWDestroyWindow_impl(WindowData* windowData)
{
	glfwDestroyWindow(windowData->nativeWindow);
	glfwTerminate();
}

void FE_API GLFWUpdate_impl(WindowData* windowData)
{
	glfwPollEvents();
	windowData->graphicsContext.SwapBuffers(windowData);
}