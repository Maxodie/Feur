#include "fepch.h"
#include "Platform/Window/GLFW/GLFWWindowsWindow.h"
#include "Feur/Core/Window/Window.h"
#include "Feur/Event/Event.h"
#include <GLFW/glfw3.h>

static void FE_DECL GLFWErrorCallback(Int32 error, const char* description);
static void FE_DECL GLFWSetWindowSizeCallback(GLFWwindow* window, Int32 width, Int32 height);
static void FE_DECL GLFWSetWindowCloseCallback(GLFWwindow* window);
static void FE_DECL GLFWSetCursorPosCallback(GLFWwindow* window, Double posX, Double posY);
static void FE_DECL GLFWSetKeyCallback(GLFWwindow* window, Int32 key, Int32 scancode, Int32 action, Int32 mods);

Bool CreateGLFWInit_impl(WindowData* windowData)
{
	return glfwInit();
}

Bool FE_DECL CreateGLFWWindow_impl(WindowData* windowData)
{
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
	glfwSetCursorPosCallback(glfwWindow, GLFWSetCursorPosCallback);

	windowData->nativeCursor = glfwCreateStandardCursor(FE_CURSOR_SHAPE_ARROW_CURSOR);
	windowData->currentCursorShape = FE_CURSOR_SHAPE_ARROW_CURSOR;
	windowData->pendingCursorShape = FE_CURSOR_SHAPE_ARROW_CURSOR;
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

static void FE_DECL GLFWErrorCallback(Int32 error, const char* description)
{
	FE_CORE_LOG_ERROR("GLFW Error ({%d}): {%s}", error, description);
}

static void FE_DECL GLFWSetWindowSizeCallback(GLFWwindow* window, Int32 width, Int32 height)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .windowData = data };
	FE_Event event = { .eventCategory = FE_EventCategory_Application, .eventType = FE_Event_WindowResize, .eventData = eventData };

	data->w = width;
	data->h = height;

	data->EventCallback(event);
}

static void FE_DECL GLFWSetWindowCloseCallback(GLFWwindow* window)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .windowData = data };
	FE_Event event = { .eventCategory = FE_EventCategory_Application, .eventType = FE_Event_WindowClose, .eventData = eventData };

	data->EventCallback(event);
}

void FE_DECL GLFWSetCursorPosCallback(GLFWwindow* window, Double posX, Double posY)
{
	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	FE_EventData eventData = { .windowData = data };
	FE_Event event = { .eventCategory = FE_EventCategory_EventCategoryMouse, .eventType = FE_Event_MouseMoved, .eventData = eventData };

	data->windowMousePos = (ILDA_vector2d){ .x = posX, .y = posY };

	data->EventCallback(event);
}

void FE_DECL GLFWSetKeyCallback(GLFWwindow* window, Int32 key, Int32 scancode, Int32 action, Int32 mods)
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


void FE_DECL GLFWPollEvent_impl()
{
	glfwPollEvents();
}

void FE_DECL GLFWDestroyWindow_impl(WindowData* windowData)
{
	glfwSetCursor(windowData->nativeCursor, windowData->nativeCursor);
	glfwDestroyWindow(windowData->nativeWindow);
	glfwTerminate();
}

void FE_DECL GLFWUpdate_impl(WindowData* windowData)
{
	if (windowData->pendingCursorShape != windowData->currentCursorShape)
	{
		GLFWcursor* cursor = glfwCreateStandardCursor(windowData->pendingCursorShape);
		if (cursor == NULL)
		{
			FE_CORE_LOG_ERROR("current cursor shape is unknown : %d", windowData->pendingCursorShape);
		}
		else
		{
			glfwDestroyCursor(windowData->nativeCursor);
			glfwSetCursor(windowData->nativeWindow, cursor);
			windowData->nativeCursor = cursor;
			windowData->currentCursorShape = windowData->pendingCursorShape;
		}
	}
	
	windowData->pendingCursorShape = FE_CURSOR_SHAPE_ARROW_CURSOR;

	windowData->graphicsContext.SwapBuffers(windowData);
}

void FE_DECL GLFWSetCursorShape_impl(WindowData* windowData, FE_CursorStandardShape shape)
{
	if (shape != windowData->pendingCursorShape)
	{
		windowData->pendingCursorShape = shape;
	}
}
