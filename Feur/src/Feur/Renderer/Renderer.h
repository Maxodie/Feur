#pragma once

BOOL FE_API InitRenderer(RendererAPI* api);
void FE_API RendererBeginScene();
void FE_API RendererEndScene();

void FE_API RendererOnWindowResize(Uint32 width, Uint32 height);

void FE_API InitRendererAPISelection();

void FE_API RendererShutdown(RendererAPIData* apiData);