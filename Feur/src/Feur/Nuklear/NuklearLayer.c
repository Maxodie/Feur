#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include <Nuklear/nuklear.h>
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"

typedef struct NuklearGUILayerInterface
{
	void (*OnEvent)(FE_Event*);
	void (*OnAttach)(Layer* layer);
	void (*OnDetach)();
	void (*OnRender)(Layer* layer);

} NuklearGUILayerInterface;

static NuklearGUILayerInterface nuklearGUILayerInterface;

void FE_DECL NuklearGUILayerInit()
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_OPENGL)
	{
		nuklearGUILayerInterface.OnAttach = OpenGL_GLFW_NuklearGUILayerOnAttach_impl;
		nuklearGUILayerInterface.OnDetach = OpenGL_GLFW_NuklearGUILayerOnDetach_impl;
		nuklearGUILayerInterface.OnEvent = OpenGL_GLFW_NuklearGUILayerEvent_impl;
		nuklearGUILayerInterface.OnRender = OpenGL_GLFW_NuklearGUILayerRender_impl;
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_VULKAN)
	{
		nuklearGUILayerInterface.OnAttach = Vulkan_GLFW_NuklearGUILayerOnAttach_impl;
		nuklearGUILayerInterface.OnDetach = Vulkan_GLFW_NuklearGUILayerOnDetach_impl;
		nuklearGUILayerInterface.OnEvent = Vulkan_GLFW_NuklearGUILayerEvent_impl;
		nuklearGUILayerInterface.OnRender = Vulkan_GLFW_NuklearGUILayerRender_impl;
	}
}

void FE_DECL NuklearGUILayerEvent(FE_Event* event)
{
	nuklearGUILayerInterface.OnEvent(event);
}

void FE_DECL NuklearGUILayerUpdate(Double dt)
{

}

void FE_DECL NuklearGUILayerRender(Layer* layer)
{
	nuklearGUILayerInterface.OnRender(layer);
}


void FE_DECL NuklearGUILayerOnAttach(Layer* layer)
{
	nuklearGUILayerInterface.OnAttach(layer);
}

void FE_DECL NuklearGUILayerOnDetach()
{
	nuklearGUILayerInterface.OnDetach();
}

Layer FE_DECL CreateNewNuklearGUILayer(char* layerName)
{
	NuklearGUILayerInit();

	Layer nuklearLayer = {
	   .layerName = layerName, .OnAttach = NuklearGUILayerOnAttach,
		   .OnDetach = NuklearGUILayerOnDetach, .OnUpdate = NuklearGUILayerUpdate, .OnUpdateLayerEvent = NuklearGUILayerEvent,
		   .OnNuklearRender = NuklearGUILayerRender, .handledInfo = NULL
	};

	 return nuklearLayer;
}