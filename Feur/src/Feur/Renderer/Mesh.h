#pragma once

typedef struct FE_Color
{
	Float32 r;
	Float32 g;
	Float32 b;
	Float32 a;
} FE_Color;

typedef struct FE_Vertex3D
{
	ILDA_vector4f position;
	ILDA_vector3f normal;
	FE_Color color;

	ILDA_vector2f texCoord;

} FE_Vertex3D;

typedef struct FE_UniformBufferObject {
	FE_ALIGN_AS(16) ILDA_matrix4x4 model;
	FE_ALIGN_AS(16) ILDA_matrix4x4 view;
	FE_ALIGN_AS(16) ILDA_matrix4x4 proj;
} FE_UniformBufferObject;

typedef struct FE_Mesh
{
	FE_List(Uint32) indices;
	FE_List(FE_Vertex3D) vertices;
} FE_Mesh;