#pragma once

BOOL InitRenderer();
void RendererBeginScene();
void RendererEndScene();

void RendererOnWindowResize(Uint32 width, Uint32 height);

void InitRendererAPISelection();