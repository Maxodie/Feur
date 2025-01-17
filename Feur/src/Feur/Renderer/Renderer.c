#include "fepch.h"
#include "Feur/Renderer/Renderer.h"
#include "Feur/Renderer/RenderCommand.h"

Bool FE_DECL InitRenderer(RendererData* api)
{
	if (!RenderCommandInit(api))
	{
		return FALSE;
	}

	return TRUE;
}

void FE_DECL RendererBeginScene()
{

}

void FE_DECL RendererEndScene()
{

}

void FE_DECL RendererOnWindowResize(Uint32 width, Uint32 height)
{
	RenderCommandOnWindowResized(0, 0, width, height, FE_Renderer2DGetIndexCount());
}

void FE_DECL RendererShutdown(RendererData* apiData)
{
	RenderCommandShutDown(apiData);
}