#include "fepch.h"
#include "Feur/Core/Window/Window.h"
#include "Platform/Windows/SDL/WindowsWindow.h"


void InitWindow()
{
	switch (window_API.API_Type)
	{
	case API_SDL:
		window_API.CreateWindow = CreateSDLWindow_impl;
		break;
	default:
		break;
	}
}

BOOL CreateWindow()
{
	return (*window_API.CreateWindow)();//put the app windowData mb?
}