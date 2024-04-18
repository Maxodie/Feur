#include "fepch.h"
#include "Feur/Core/Window/Window.h"
#include "Platform/Windows/SDL/SDLWindowsWindow.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"

void InitWindow()
{

	g_Window_API.API_Type = WINDOW_API_SDL;
	switch (g_Window_API.API_Type)
	{
	case WINDOW_API_SDL:
		g_Window_API.CreateWindow = CreateSDLWindow_impl;
		g_Window_API.DestroyWindow = SDLDestroyWindow_impl;
		g_Window_API.PollEvent = SDLPollEvent_impl;
		break;
	case WINDOW_API_GLFW:
		g_Window_API.CreateWindow = CreateGLFWWindow_impl;
		g_Window_API.DestroyWindow = GLFWDestroyWindow_impl;
		g_Window_API.PollEvent = GLFWPollEvent_impl;
		break;
	default:
		break;
	}
}

BOOL CreateWindow()
{
	return (*g_Window_API.CreateWindow)();//put the app windowData mb?
}