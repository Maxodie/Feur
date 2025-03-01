#pragma once


typedef enum Renderer_API_Type { FE_RENDERER_API_TYPE_OPENGL, FE_RENDERER_API_TYPE_VULKAN } Renderer_API_Type;

typedef struct RendererData
{
	FE_Color defaultClearColor;
	char* pendingVertexShaderPath;
	char* pendingFragmentShaderPath;
	void* nativeInfoAPI;
} RendererData;

typedef struct RendererAPI
{
	Bool (*Init)(RendererData* api);
	
	void (*FramePrepare)();
	Bool (*FrameCommandListBegin)();
	void (*BeginRendering)(FE_Color* clearColor);
	void (*SetViewport)(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
	void (*SetScissor)(Uint32 width, Uint32 height);
	void (*BindPipeline)();

	void (*BeginScene)(const FE_Camera3D* cam);
	void (*EndScene)();
	void (*DrawIndex)(Uint32 indexCount, SizeT indexBufferId, SizeT vertexBufferId);

	void (*EndRendering)();
	Bool (*FrameCommandListEnd)();
	Bool (*FrameSubmit)();
	Bool (*FramePresent)();
	void (*WaitIdle)();

	void (*Shutdown)();

	void (*OnWindowResized)(Uint32 x, Uint32 y, Uint32 width, Uint32 height);

	// images
	void* (*GetFrameImageView)();
	// images

	//Shaders
	void (*UpdatePendingRenderPipelineShaders)();
	//Shaders

	FE_BufferAPI bufferAPI;
	Renderer_API_Type API_Type;
} RendererAPI;

void FE_DECL InitRendererAPISelection(RendererData* apiData);
const RendererAPI* FE_DECL GetRendererAPI();