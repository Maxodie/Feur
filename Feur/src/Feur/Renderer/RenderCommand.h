#pragma once

BOOL RenderCommandInit();
void RenderCommandClearScreenColor();
void RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height);
void RenderCommandClear();
void RenderCommandDrawIndex();