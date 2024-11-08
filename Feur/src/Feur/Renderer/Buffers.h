#pragma once

typedef struct Renderer_VAO_Buffer 
{
	void (*InitVaoBuffer)();
} Renderer_VAO_Buffer;

typedef struct FE_Vertex3D
{
	ILDA_vector3f position;
	ILDA_vector3f color;
} FE_Vertex3D;

Renderer_VAO_Buffer* FE_API GetRenderer_VertexArray_Buffer();