#pragma once


typedef enum Renderer_API_Type { FE_RENDERER_API_TYPE_OPENGL, FE_RENDERER_API_TYPE_VULKAN } Renderer_API_Type;

typedef struct RendererAPIData
{
	FE_Color defaultClearColor;
	void* nativeInfoAPI;
} RendererAPIData;

typedef struct RendererAPI
{
	Bool (*Init)(RendererAPIData* api);

	void (*FramePrepare)();
	Bool (*FrameCommandListBegin)();
	void (*BeginRendering)(FE_Color* clearColor);
	void (*SetViewport)(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
	void (*SetScissor)(Uint32 width, Uint32 height);
	void (*BindPipeline)();

	void (*BeginScene)(const FE_Camera3D* cam);//put cam here
	void (*EndScene)();
	void (*DrawIndex)(Uint32 indexCount);


	void (*EndRendering)();
	Bool (*FrameCommandListEnd)();
	Bool (*FrameSubmit)();
	Bool (*FramePresent)();
	void (*WaitIdle)();

	void (*Shutdown)();

	void (*OnWindowResized)(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 drawIndexCount);

	FE_BufferAPI bufferAPI;
	Renderer_API_Type API_Type;
} RendererAPI;

void FE_DECL InitRendererAPISelection(RendererAPIData* apiData);
const RendererAPI* FE_DECL GetRendererAPI();