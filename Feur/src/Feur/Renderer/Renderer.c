#include "fepch.h"
#include "Feur/Renderer/Renderer.h"
#include "Feur/Renderer/RenderCommand.h"

Bool FE_API InitRenderer(RendererAPIData* api)
{
	if (!RenderCommandInit(api))
	{
		return FALSE;
	}

	return TRUE;
}

void FE_API RendererBeginScene()
{

}

void FE_API RendererEndScene()
{

}

void FE_API RendererOnWindowResize(Uint32 width, Uint32 height)
{
	RenderCommandSetRendererViewport(0, 0, width, height);
}

void FE_API RendererShutdown(RendererAPIData* apiData)
{
	RenderCommandShutDown(apiData);
}