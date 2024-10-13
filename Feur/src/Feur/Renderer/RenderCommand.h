#pragma once

Bool FE_API RenderCommandInit(RendererAPIData* api);
void FE_API RenderCommandClearScreenColor();
void FE_API RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height);
void FE_API RenderCommandClear();
void FE_API RenderCommandDrawIndex();
void FE_API RenderCommandShutDown(RendererAPIData* apiData);