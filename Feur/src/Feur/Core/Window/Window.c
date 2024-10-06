#include "fepch.h"
#include "Feur/Core/Window/Window.h"
#include "Platform/Windows/SDL/SDLWindowsWindow.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"

static Window_API windowAPI;

void FE_API InitWindowAPI()
{
	windowAPI.API_Type = FE_WINDOW_API_GLFW;
	switch (windowAPI.API_Type)
	{
	case FE_WINDOW_API_SDL:
		windowAPI.CreateWindow = CreateSDLWindow_impl;
		windowAPI.DestroyWindow = SDLDestroyWindow_impl;
		windowAPI.PollEvent = SDLPollEvent_impl;
		//windowAPI.Update = SDLUpdate_impl;
		break;
	case FE_WINDOW_API_GLFW:
		windowAPI.CreateWindow = CreateGLFWWindow_impl;
		windowAPI.DestroyWindow = GLFWDestroyWindow_impl;
		windowAPI.PollEvent = GLFWPollEvent_impl;
		windowAPI.Update = GLFWUpdate_impl;
		break;
	default:
		break;
	}
}

void FE_API CreateWindow(WindowData* windowData)
{
	InitWindowCreationHintParameters();
	BOOL success = windowAPI.CreateWindow(windowData);

	FE_CORE_ASSERT(success, "Window.c: Failed to create window");

	CreateGraphicsContext(windowData);
}

Window_API* FE_API GetWindowAPI()
{
	return &windowAPI;
}
