#pragma once

typedef enum { FE_RENDERER_API_OPENGL, FE_RENDERER_API_VULKAN } Renderer_API_Type;

typedef struct RendererAPIData
{
	void* nativeInfoAPI;
} RendererAPIData;

typedef struct RendererAPI
{
	BOOL (*Init)(RendererAPIData* api);
	void (*SetViewport)(Uint32, Uint32, Uint32, Uint32);
	void (*Clear)();
	void (*ClearScreenColor)();
	void (*DrawIndex)();
	void (*Shutdown)(RendererAPIData* apiData);

	Renderer_API_Type API_Type;
} RendererAPI;

void FE_API InitRendererAPISelection();
const RendererAPI* FE_API GetRendererAPI();