#include "fepch.h"
#include "Feur/Renderer/Buffers.h"

Renderer_VAO_Buffer renderer_VAO_Buffer;

Renderer_VAO_Buffer* FE_API GetRenderer_VertexArray_Buffer()
{
	return &renderer_VAO_Buffer;
}
