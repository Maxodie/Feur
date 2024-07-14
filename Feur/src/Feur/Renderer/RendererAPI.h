#pragma once

typedef enum { FE_RENDERER_API_OPENGL } Renderer_API_Type;

typedef struct RendererAPI
{
	BOOL(*Init)();
	void (*SetViewport)(Uint32, Uint32, Uint32, Uint32);
	void (*Clear)();
	void (*ClearScreenColor)();
	void (*DrawIndex)();

	Renderer_API_Type API_Type;
} RendererAPI;

void InitRendererAPISelection();
const RendererAPI* GetRendererAPI();