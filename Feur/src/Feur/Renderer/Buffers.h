#pragma once

typedef struct Renderer_VAO_Buffer {
	void (*InitVaoBuffer)();
} Renderer_VAO_Buffer;


Renderer_VAO_Buffer* FE_API GetRenderer_VertexArray_Buffer();