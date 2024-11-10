#include "fepch.h"
#include "Feur/Renderer/RendererAPI.h"
#include "Feur/Renderer/Buffers.h"

#include "Platform/OpenGL/OpenGLRendererAPIimpl.h"
#include "Platform/OpenGL/OpenGLBuffers.h"
#include "Platform/Vulkan/VulkanRendererAPIimpl.h"
#include "Platform/Vulkan/VulkanBuffers.h"

static RendererAPI rendererAPI;

void InitRendererAPISelection(RendererAPIData* apiData)
{
	apiData->defaultClearColor = (ILDA_vector4f){ .x = 120, .y = 200, .z = 40, .w = 255 };

#ifdef FE_RENDER_SELECTED_API_OPENGL
	rendererAPI.API_Type = FE_RENDERER_API_TYPE_OPENGL;
#elif defined(FE_RENDER_SELECTED_API_VULKAN)
	rendererAPI.API_Type = FE_RENDERER_API_TYPE_VULKAN;
#endif

	switch (rendererAPI.API_Type)
	{
	case FE_RENDERER_API_TYPE_OPENGL:
		rendererAPI.BeginRendering = OpenGLBeginRendering_impl;
		rendererAPI.DrawIndex = OpenGLDrawIndex_impl;
		rendererAPI.OnWindowResized = OpenGLOnWindowResize_impl;
		rendererAPI.Init = OpenGLInit_impl;
		rendererAPI.Shutdown = OpenGLShutdown_impl;

		GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitOpenGL_VertexArrayBuffer;
		break;

	case FE_RENDERER_API_TYPE_VULKAN:
		rendererAPI.Init = VulkanInit_impl;

		rendererAPI.FramePrepare = VulkanFramePrepare_impl;
		rendererAPI.FrameCommandListBegin = VulkanFrameCommandListBegin_impl;
		rendererAPI.BeginRendering = VulkanBeginRendering_impl;
		rendererAPI.SetViewport = VulkanSetViewport_impl;
		rendererAPI.SetScissor = VulkanSetScissor_impl;
		rendererAPI.BindPipeline = VulkanBindPipeline_impl;
		rendererAPI.DrawIndex = VulkanDrawIndex_impl;
		rendererAPI.EndRendering = VulkanEndRendering_impl;
		rendererAPI.FrameCommandListEnd = VulkanFrameCommandListEnd_impl;
		rendererAPI.FrameSubmit = VulkanFrameSubmit_impl;
		rendererAPI.FramePresent = VulkanFramePresent_impl;
		rendererAPI.WaitIdle = VulkanWaitIdle_impl;

		rendererAPI.Shutdown = VulkanShutdown_impl;

		rendererAPI.OnWindowResized = VulkanOnWindowResized_impl;

		GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitVulkan_VertexArrayBuffer;
		break;

	default:
		FE_CORE_LOG_ERROR("RendererAPI : No render API Selected");
		break;
	}
}

const RendererAPI* GetRendererAPI()
{
	return &rendererAPI;
}
