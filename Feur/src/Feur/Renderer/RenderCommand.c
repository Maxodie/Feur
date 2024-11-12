#include "fepch.h"
#include "RenderCommand.h"

#include "Feur/Renderer/RendererAPI.h"

Bool RenderCommandInit(RendererAPIData* api)
{
	return GetRendererAPI()->Init(api);
}

void RenderCommandFramePrepare()
{
	GetRendererAPI()->FramePrepare();
}

void RenderCommandFrameCommandListBegin()
{
	GetRendererAPI()->FrameCommandListBegin();
}

void FE_DECL RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth)
{
	GetRendererAPI()->SetViewport(w, h, width, height, minDepth, maxDepth);
}

void RenderCommandSetScissor(Uint32 width, Uint32 height)
{
	GetRendererAPI()->SetScissor(width, height);
}

void RenderCommandBindPipeline()
{
	GetRendererAPI()->BindPipeline();
}

void FE_DECL RenderCommandBeginRendering(ILDA_vector4f * clearColor)
{
	GetRendererAPI()->BeginRendering(clearColor);
}

void FE_DECL RenderCommandDrawIndex()
{
	GetRendererAPI()->DrawIndex();
}

void RenderCommandEndRendering()
{
	GetRendererAPI()->EndRendering();
}

void RenderCommandFrameCommandListEnd()
{
	GetRendererAPI()->FrameCommandListEnd();
}

void RenderCommandFrameSubmit()
{
	GetRendererAPI()->FrameSubmit();
}

void RenderCommandFramePresent()
{
	GetRendererAPI()->FramePresent();
}

void RenderCommandWaitIdle()
{
	GetRendererAPI()->WaitIdle();
}

void RenderCommandShutDown()
{
	GetRendererAPI()->Shutdown();
}

void RenderCommandOnWindowResized(Uint32 w, Uint32 h, Uint32 width, Uint32 height)
{
	GetRendererAPI()->OnWindowResized(w, h, width, height);
}
