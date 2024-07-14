#include "fepch.h"
#include "Feur/Renderer/Renderer.h"
#include "Feur/Renderer/RenderCommand.h"

BOOL InitRenderer()
{
	if (!RenderCommandInit())
	{
		return FALSE;
	}

	return TRUE;
}

void RendererBeginScene()
{
	
}

void RendererEndScene()
{

}

void RendererOnWindowResize(Uint32 width, Uint32 height)
{
	RenderCommandSetRendererViewport(0, 0, width, height);
}