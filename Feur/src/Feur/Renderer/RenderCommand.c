#include "fepch.h"
#include "RenderCommand.h"

#include "Feur/Renderer/RendererAPI.h"

BOOL RenderCommandInit()
{
	return GetRendererAPI()->Init();
}

void RenderCommandClearScreenColor()
{
	GetRendererAPI()->ClearScreenColor();
}

void RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height)
{
	GetRendererAPI()->SetViewport(w, h, width, height);
}

void RenderCommandClear()
{
	GetRendererAPI()->Clear();
}

void RenderCommandDrawIndex()
{
	GetRendererAPI()->DrawIndex();
}
