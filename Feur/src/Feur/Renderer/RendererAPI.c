#include "fepch.h"
#include "Feur/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

static RendererAPI rendererAPI;

void InitRendererAPISelection()
{
	rendererAPI.API_Type = FE_RENDERER_API_OPENGL;
	switch (rendererAPI.API_Type)
	{
	case FE_RENDERER_API_OPENGL:
		rendererAPI.Clear = OpenGLClear_impl;
		rendererAPI.ClearScreenColor = OpenGLClearScreenColor_impl;
		rendererAPI.DrawIndex = OpenGLDrawIndex_impl;
		rendererAPI.SetViewport = OpenGLSetViewport_impl;
		rendererAPI.Init = OpenGLInit_Impl;
		break;
	default:
		break;
	}
}

const RendererAPI* GetRendererAPI()
{
	return &rendererAPI;
}
