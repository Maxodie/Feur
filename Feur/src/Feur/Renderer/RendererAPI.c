#include "fepch.h"
#include "Feur/Renderer/RendererAPI.h"
#include "Feur/Renderer/Buffers.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffers.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"
#include "Platform/Vulkan/VulkanBuffers.h"

static RendererAPI rendererAPI;

void FE_API InitRendererAPISelection()
{
#ifdef FE_RENDER_SELECTED_API_OPENGL
	rendererAPI.API_Type = FE_RENDERER_API_OPENGL;
#elif defined(FE_RENDER_SELECTED_API_VULKAN)
	rendererAPI.API_Type = FE_RENDERER_API_VULKAN;
#endif

	switch (rendererAPI.API_Type)
	{
	case FE_RENDERER_API_OPENGL:
		rendererAPI.Clear = OpenGLClear_impl;
		rendererAPI.ClearScreenColor = OpenGLClearScreenColor_impl;
		rendererAPI.DrawIndex = OpenGLDrawIndex_impl;
		rendererAPI.SetViewport = OpenGLSetViewport_impl;
		rendererAPI.Init = OpenGLInit_impl;
		rendererAPI.Shutdown = OpenGLShutdown_impl;

		GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitOpenGL_VertexArrayBuffer;
		break;

	case FE_RENDERER_API_VULKAN:
		rendererAPI.Clear = VulkanClear_impl;
		rendererAPI.ClearScreenColor = VulkanClearScreenColor_impl;
		rendererAPI.DrawIndex = VulkanDrawIndex_impl;
		rendererAPI.SetViewport = VulkanSetViewport_impl;
		rendererAPI.Init = VulkanInit_impl;
		rendererAPI.Shutdown = VulkanShutdown_impl;

		GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitVulkan_VertexArrayBuffer;
		break;

	default:
		FE_CORE_LOG_ERROR("RendererAPI : No render API Selected");
		break;
	}
}

const RendererAPI* FE_API GetRendererAPI()
{
	return &rendererAPI;
}
