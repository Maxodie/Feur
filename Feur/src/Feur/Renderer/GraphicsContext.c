#include "fepch.h"
#include "Feur/Renderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLGraphicsContext.h"
#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include <GLFW/glfw3.h>

void FE_API InitWindowCreationHintParameters()
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_OPENGL)
	{
		OpenGL_GLFWwindowHintParameters();
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_VULKAN)
	{
		Vulkan_GLFWwindowHintParameters();
	}
	else
	{
		FE_CORE_ASSERT(0, "GraphicsContext.c: Failed to CreateHintParameter for the current specifications");
	}
}

void FE_API CreateGraphicsContext(WindowData* windowData)
{
	if(GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_OPENGL)
	{
		windowData->graphicsContext.Init = OpenGL_GLFWgraphicsContextInit;
		windowData->graphicsContext.SwapBuffers = OpenGL_GLFWGraphicsContextSwapBuffers;
		windowData->graphicsContext.windowHandle = (GLFWwindow*)windowData->nativeWindow;
		return;
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_VULKAN)
	{
		windowData->graphicsContext.Init = Vulkan_GLFWgraphicsContextInit;
		windowData->graphicsContext.SwapBuffers = Vulkan_GLFWgraphicsContextSwapBuffers;
		windowData->graphicsContext.windowHandle = (GLFWwindow*)windowData->nativeWindow;
		return;
	}
	else
	{
		FE_CORE_ASSERT(0, "GraphicsContext.c: Failed to select graphicsContext");
	}
}