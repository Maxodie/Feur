#pragma once

Bool FE_DECL RenderCommandInit(RendererAPIData* api);

void FE_DECL RenderCommandFramePrepare();
void FE_DECL RenderCommandFrameCommandListBegin();
void FE_DECL RenderCommandBeginRendering(FE_Color* clearColor);
void FE_DECL RenderCommandSetRendererViewport(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
void FE_DECL RenderCommandSetScissor(Uint32 width, Uint32 height);
void FE_DECL RenderCommandBindPipeline();


void FE_DECL RenderCommandBeginScene(const FE_Camera3D * cam);
void FE_DECL RenderCommandEndScene();
void FE_DECL RenderCommandDrawIndex(Uint32 indexCount);


void FE_DECL RenderCommandEndRendering();
void FE_DECL RenderCommandFrameCommandListEnd();
void FE_DECL RenderCommandFrameSubmit();
void FE_DECL RenderCommandFramePresent();
void FE_DECL RenderCommandWaitIdle();

void FE_DECL RenderCommandShutDown();

void FE_DECL RenderCommandOnWindowResized(Uint32 w, Uint32 h, Uint32 width, Uint32 height, Uint32 drawIndexCount);