#pragma once

Bool RenderCommandInit(RendererAPIData* api);

void FE_API RenderCommandFramePrepare();
void FE_API RenderCommandFrameCommandListBegin();
void FE_API RenderCommandBeginRendering(ILDA_vector4f * clearColor);
void FE_API RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
void FE_API RenderCommandSetScissor(Uint32 width, Uint32 height);
void FE_API RenderCommandBindPipeline();
void FE_API RenderCommandDrawIndex();
void FE_API RenderCommandEndRendering();
void FE_API RenderCommandFrameCommandListEnd();
void FE_API RenderCommandFrameSubmit();
void FE_API RenderCommandFramePresent();
void FE_API RenderCommandWaitIdle();

void RenderCommandShutDown();

void FE_API RenderCommandOnWindowResized(Uint32 w, Uint32 h, Uint32 width, Uint32 height);