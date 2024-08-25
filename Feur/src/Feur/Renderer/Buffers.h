#pragma once

typedef struct Renderer_VAO_Buffer {
	void (*InitVaoBuffer)();
} Renderer_VAO_Buffer;


Renderer_VAO_Buffer* GetRenderer_VertexArray_Buffer();