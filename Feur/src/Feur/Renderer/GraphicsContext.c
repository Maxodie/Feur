#include "fepch.h"
#include "Feur/Renderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLGraphicsContext.h"
#include <GLFW/glfw3.h>

void CreateGraphicsContext(WindowData* windowData)
{
	if(GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_OPENGL)
	{
		windowData->graphicsContext.Init = OpenGLG_GLFWraphicsContextInit;
		windowData->graphicsContext.SwapBuffers = OpenGL_GLFWGraphicsContextSwapBuffers;
		windowData->graphicsContext.windowHandle = (GLFWwindow*)windowData->nativeWindow;
		return;
	}

	FE_CORE_ASSERT(0, "GraphicsContext.c: Failed to select graphicsContext");
}