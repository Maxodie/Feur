#pragma once

Bool FE_DECL InitRenderer(RendererData* api);
void FE_DECL RendererBeginScene();
void FE_DECL RendererEndScene();

void FE_DECL RendererOnWindowResize(Uint32 width, Uint32 height);

void FE_DECL RendererShutdown(RendererData* apiData);