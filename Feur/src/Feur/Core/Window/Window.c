#include "fepch.h"
#include "Feur/Core/Window/Window.h"
#include "Platform/Window/SDL/SDLWindowsWindow.h"
#include "Platform/Window/GLFW/GLFWWindowsWindow.h"

static Window_API windowAPI;

void FE_API InitWindowAPI()
{
	windowAPI.API_Type = FE_WINDOW_API_GLFW;
	switch (windowAPI.API_Type)
	{
	case FE_WINDOW_API_SDL:
		windowAPI.CreateAppWindow = CreateSDLWindow_impl;
		windowAPI.DestroyWindow = SDLDestroyWindow_impl;
		windowAPI.PollEvent = SDLPollEvent_impl;
		//windowAPI.Update = SDLUpdate_impl;
		break;
	case FE_WINDOW_API_GLFW:
		windowAPI.Init = CreateGLFWInit_impl;
		windowAPI.CreateAppWindow = CreateGLFWWindow_impl;
		windowAPI.DestroyWindow = GLFWDestroyWindow_impl;
		windowAPI.PollEvent = GLFWPollEvent_impl;
		windowAPI.Update = GLFWUpdate_impl;
		break;
	default:
		break;
	}
}

void FE_API CreateAppWindow(WindowData* windowData)
{
	Bool success = windowAPI.Init();
	FE_CORE_ASSERT(success, "Failed to init window");

	InitWindowCreationHintParameters();

	success = windowAPI.CreateAppWindow(windowData);
	FE_CORE_ASSERT(success, "Window.c: Failed to create window");

	CreateGraphicsContext(windowData);
}

const Window_API* FE_API GetWindowAPI()
{
	return &windowAPI;
}
