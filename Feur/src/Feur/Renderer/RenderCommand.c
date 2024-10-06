#include "fepch.h"
#include "RenderCommand.h"

#include "Feur/Renderer/RendererAPI.h"

BOOL FE_API RenderCommandInit(RendererAPIData* api)
{
	return GetRendererAPI()->Init(api);
}

void FE_API RenderCommandClearScreenColor()
{
	GetRendererAPI()->ClearScreenColor();
}

void FE_API RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height)
{
	GetRendererAPI()->SetViewport(w, h, width, height);
}

void FE_API RenderCommandClear()
{
	GetRendererAPI()->Clear();
}

void FE_API RenderCommandDrawIndex()
{
	GetRendererAPI()->DrawIndex();
}

void FE_API RenderCommandShutDown(RendererAPIData* apiData)
{
	return GetRendererAPI()->Shutdown(apiData);
}