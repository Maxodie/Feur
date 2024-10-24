#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include "Platform/Nuklear/OpenGLNuklearLayer.h"

typedef struct NuklearGUILayerInterface
{
	void (*OnEvent)(FE_Event*);
	void (*OnAttach)(Layer* layer);
	void (*OnDetach)();
	void (*OnRender)(Layer* layer);

} NuklearGUILayerInterface;

static NuklearGUILayerInterface nuklearGUILayerInterface;

void FE_API NuklearGUILayerInit()
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_OPENGL)
	{
		nuklearGUILayerInterface.OnAttach = OpenGL_GLFW_NuklearGUILayerOnAttach_impl;
		nuklearGUILayerInterface.OnDetach = OpenGL_GLFW_NuklearGUILayerOnDetach_impl;
		nuklearGUILayerInterface.OnEvent = OpenGL_GLFW_NuklearGUILayerEvent_impl;
		nuklearGUILayerInterface.OnRender = OpenGL_GLFW_NuklearGUILayerRender_impl;
	}
}

void FE_API NuklearGUILayerEvent(FE_Event* event)
{
#ifdef FE_RENDER_SELECTED_API_OPENGL
	nuklearGUILayerInterface.OnEvent(event);
#endif
}

void FE_API NuklearGUILayerUpdate()
{

}

void FE_API NuklearGUILayerRender(Layer* layer)
{
#ifdef FE_RENDER_SELECTED_API_OPENGL
	nuklearGUILayerInterface.OnRender(layer);
#endif
}


void FE_API NuklearGUILayerOnAttach(Layer* layer)
{
#ifdef FE_RENDER_SELECTED_API_OPENGL
	nuklearGUILayerInterface.OnAttach(layer);
#endif
}

void FE_API NuklearGUILayerOnDetach()
{
#ifdef FE_RENDER_SELECTED_API_OPENGL
	nuklearGUILayerInterface.OnDetach();
#endif
}

Layer FE_API CreateNewNuklearGUILayer(char* layerName)
{
	NuklearGUILayerInit();

	Layer nuklearLayer = {
	   .layerName = layerName, .OnAttach = NuklearGUILayerOnAttach,
		   .OnDetach = NuklearGUILayerOnDetach, .OnUpdate = NuklearGUILayerUpdate, .OnUpdateLayerEvent = NuklearGUILayerEvent,
		   .OnRender = NuklearGUILayerRender, .handledInfo = NULL
	};

	 return nuklearLayer;
}