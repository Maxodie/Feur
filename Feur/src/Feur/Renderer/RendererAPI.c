#include "fepch.h"
#include "Feur/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPIimpl.h"
#include "Platform/Vulkan/VulkanRendererAPIimpl.h"

static RendererAPI rendererAPI;

void FE_DECL InitRendererAPISelection(RendererData* apiData)
{
	apiData->defaultClearColor = (FE_Color){ .r = 0.01f, .g = 0.01f, .b = 0.01f, .a = 1 };
	apiData->pendingVertexShaderPath = "vulkan/VertexShader.vert";
	apiData->pendingFragmentShaderPath = "vulkan/FragmentShader.frag";

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

		//GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitOpenGL_VertexArrayBuffer;
		break;

	case FE_RENDERER_API_TYPE_VULKAN:
		rendererAPI.Init = VulkanInit_impl;

		rendererAPI.FramePrepare = VulkanFramePrepare_impl;
		rendererAPI.FrameCommandListBegin = VulkanFrameCommandListBegin_impl;
		rendererAPI.BeginRendering = VulkanBeginRendering_impl;
		rendererAPI.SetViewport = VulkanSetViewport_impl;
		rendererAPI.SetScissor = VulkanSetScissor_impl;
		rendererAPI.BindPipeline = VulkanBindPipeline_impl;

		rendererAPI.BeginScene = VulkanBeginScene_impl;
		rendererAPI.EndScene = VulkanEndScene_impl;
		rendererAPI.DrawIndex = VulkanDrawIndex_impl;


		rendererAPI.EndRendering = VulkanEndRendering_impl;
		rendererAPI.FrameCommandListEnd = VulkanFrameCommandListEnd_impl;
		rendererAPI.FrameSubmit = VulkanFrameSubmit_impl;
		rendererAPI.FramePresent = VulkanFramePresent_impl;
		rendererAPI.WaitIdle = VulkanWaitIdle_impl;

		rendererAPI.Shutdown = VulkanShutdown_impl;

		rendererAPI.OnWindowResized = VulkanOnWindowResized_impl;
		
		//images
		rendererAPI.GetFrameImageView = VulkanGetFrameImageView;
		//images

		//shaders TODO : shader api
		rendererAPI.UpdatePendingRenderPipelineShaders = VulkanUpdatePendingShaders_impl;
		//shaders

		//buffers
		rendererAPI.bufferAPI.CreateVertexBuffer = VulkanCreateVertexBuffer_impl;
		rendererAPI.bufferAPI.AddVertexIntoBuffer = VulkanAddVertexIntoBuffer_impl;
		rendererAPI.bufferAPI.CreateIndexBuffer = VulkanCreateIndexBuffer_impl;
		rendererAPI.bufferAPI.AddIndexIntoBuffer = VulkanAddIndexIntoBuffer_impl;

		rendererAPI.bufferAPI.DestroyVertexBuffer = VulkanDestroyVertexBuffer_impl;
		rendererAPI.bufferAPI.DestroyIndexBuffer = VulkanDestroyIndexBuffer_impl;


		//GetRenderer_VertexArray_Buffer()->InitVaoBuffer = InitVulkan_VertexArrayBuffer;
		break;

	default:
		FE_CORE_LOG_ERROR("RendererAPI : No render API Selected");
		break;
	}
}

const RendererAPI* FE_DECL GetRendererAPI()
{
	return &rendererAPI;
}
