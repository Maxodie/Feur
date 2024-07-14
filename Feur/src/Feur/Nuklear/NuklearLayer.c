#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include "Platform/Nuklear/OpenGLNuklearLayer.h"

typedef struct NuklearGUILayerInterface
{
	void (*Update)();
	void (*OnEvent)();
	void (*OnAttach)();
	void (*OnDetach)();
} NuklearGUILayerInterface;

static NuklearGUILayerInterface nuklearGUILayerInterface;

void NuklearGUILayerInit()
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_OPENGL)
	{
		nuklearGUILayerInterface.OnAttach = OpenGL_GLFW_NuklearGUILayerOnAttach_impl;
		nuklearGUILayerInterface.OnDetach = OpenGL_GLFW_NuklearGUILayerOnDetach_impl;
		nuklearGUILayerInterface.OnEvent = OpenGL_GLFW_NuklearGUILayerEvent_impl;
		nuklearGUILayerInterface.Update = OpenGL_GLFW_NuklearGUILayerUpdate_impl;
	}
}

void NuklearGUILayerUpdate()
{
}

void NuklearGUILayerEvent(FE_Event* event)
{
}

void NuklearGUILayerOnAttach()
{
}

void NuklearGUILayerOnDetach()
{
}

Layer CreateNewNuklearGUILayer(const char* layerName)
{
	return (Layer) {
		.layerName = layerName, .OnAttach = NuklearGUILayerOnAttach,
			.OnDetach = NuklearGUILayerOnDetach, .OnUpdate = NuklearGUILayerUpdate, .OnUpdateLayerEvent = NuklearGUILayerEvent
	};
}