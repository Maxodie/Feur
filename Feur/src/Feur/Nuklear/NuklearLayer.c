#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include <Nuklear/nuklear.h>
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"

void FE_DECL NuklearGUIInterfaceInit(NuklearGUIInterface* interface)
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_OPENGL)
	{
		interface->Init = OpenGL_GLFW_NuklearGUIInit_impl;
		interface->Shutdown = OpenGL_GLFW_NuklearGUIShutdown_impl;
		interface->OnEvent = OpenGL_GLFW_NuklearGUIEvent_impl;
		interface->OnEndRender = OpenGL_GLFW_NuklearGUIEndRender_impl;
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_VULKAN)
	{
		interface->Init = Vulkan_GLFW_NuklearGUIInit_impl;
		interface->Shutdown = Vulkan_GLFW_NuklearGUIShutdown_impl;
		interface->OnEvent = Vulkan_GLFW_NuklearGUIEvent_impl;
		interface->OnBeginRender = Vulkan_GLFW_NuklearGUIBeginRender_impl;
		interface->OnEndRender = Vulkan_GLFW_NuklearGUIEndRender_impl;
		interface->OnWindowResize = Vulkan_GLFW_NuklearGUIOnWindowResize_impl;
	}
}