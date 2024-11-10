#pragma once

typedef enum { FE_RENDERER_API_TYPE_OPENGL, FE_RENDERER_API_TYPE_VULKAN } Renderer_API_Type;

typedef struct RendererAPIData
{
	void* nativeInfoAPI;
} RendererAPIData;

typedef struct RendererAPI
{
	Bool (*Init)(RendererAPIData* api);

	void (*FramePrepare)();
	Bool(*FrameCommandListBegin)();
	void (*BeginRendering)(ILDA_vector4f* clearColor);
	void (*SetViewport)(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
	void (*SetScissor)(Uint32 width, Uint32 height);
	void (*BindPipeline)();
	void (*DrawIndex)();
	void (*EndRendering)();
	Bool (*FrameCommandListEnd)();
	Bool (*FrameSubmit)();
	Bool (*FramePresent)();
	void (*WaitIdle)();

	void (*Shutdown)();

	void (*OnWindowResized)(Uint32 x, Uint32 y, Uint32 width, Uint32 height);

	Renderer_API_Type API_Type;
} RendererAPI;

void InitRendererAPISelection();
const RendererAPI* GetRendererAPI();