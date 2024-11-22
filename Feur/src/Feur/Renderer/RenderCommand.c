#include "fepch.h"
#include "RenderCommand.h"


Bool FE_DECL RenderCommandInit(RendererAPIData* api)
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

void FE_DECL RenderCommandBeginScene(const FE_Camera* cam)
{
	GetRendererAPI()->BeginScene(cam);
}

void FE_DECL RenderCommandEndScene()
{
	GetRendererAPI()->EndScene();
}

void FE_DECL RenderCommandDrawIndex(Uint32 indexCount)
{
	GetRendererAPI()->DrawIndex(indexCount);
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
