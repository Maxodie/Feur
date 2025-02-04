#include "fepch.h"
#include "RenderCommand.h"


Bool FE_DECL RenderCommandInit(RendererData* api)
{
	return GetRendererAPI()->Init(api);
}

void FE_DECL RenderCommandFramePrepare()
{
	GetRendererAPI()->FramePrepare();
}

void FE_DECL RenderCommandFrameCommandListBegin()
{
	GetRendererAPI()->FrameCommandListBegin();
}

void FE_DECL RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth)
{
	GetRendererAPI()->SetViewport(w, h, width, height, minDepth, maxDepth);
}

void FE_DECL RenderCommandSetScissor(Uint32 width, Uint32 height)
{
	GetRendererAPI()->SetScissor(width, height);
}

void FE_DECL RenderCommandBindPipeline()
{
	GetRendererAPI()->BindPipeline();
}

void FE_DECL RenderCommandBeginRendering(FE_Color* clearColor)
{
	GetRendererAPI()->BeginRendering(clearColor);
}

void FE_DECL RenderCommandBeginScene(const FE_Camera3D* cam)
{
	GetRendererAPI()->BeginScene(cam);
}

void FE_DECL RenderCommandEndScene()
{
	GetRendererAPI()->EndScene();
}

void FE_DECL RenderCommandDrawIndex(Uint32 indexCount, SizeT indexBufferId, SizeT vertexBufferId)
{
	GetRendererAPI()->DrawIndex(indexCount, indexBufferId, vertexBufferId);
}

void FE_DECL RenderCommandEndRendering()
{
	GetRendererAPI()->EndRendering();
}

void FE_DECL RenderCommandFrameCommandListEnd()
{
	GetRendererAPI()->FrameCommandListEnd();
}

void FE_DECL RenderCommandFrameSubmit()
{
	GetRendererAPI()->FrameSubmit();
}

void FE_DECL RenderCommandFramePresent()
{
	GetRendererAPI()->FramePresent();
}

void FE_DECL RenderCommandWaitIdle()
{
	GetRendererAPI()->WaitIdle();
}

void FE_DECL RenderCommandShutDown()
{
	GetRendererAPI()->Shutdown();
}

void FE_DECL RenderCommandOnWindowResized(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 drawIndexCount)
{
	GetRendererAPI()->OnWindowResized(w, h, width, height, drawIndexCount);
}

void* FE_DECL RenderCommandGetFrameImageView()
{
	return GetRendererAPI()->GetFrameImageView();
}

void FE_DECL UpdateGraphicsPipelineShaders()
{
	FE_CORE_LOG_SUCCESS("Start updating graphics pipeline shaders");
	GetRendererAPI()->UpdatePendingRenderPipelineShaders();
}

void FE_DECL RenderCommandPostTaskUpdateGraphicsPipelineShaders()
{
	FE_EventPostTask(&GetApp()->eventRegistry, UpdateGraphicsPipelineShaders);
}

void FE_DECL RenderCommandChangeGraphicsPipelineShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	FE_App* app = GetApp();
	if (vertexShaderPath != NULL)
	{
		app->rendererData.pendingVertexShaderPath = vertexShaderPath;
	}

	if (fragmentShaderPath != NULL)
	{
		app->rendererData.pendingFragmentShaderPath = fragmentShaderPath;
	}
}


