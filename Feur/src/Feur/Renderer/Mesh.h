#pragma once

typedef struct FE_Vertex3D
{
	ILDA_vector3f position;
	ILDA_vector3f normal;
	ILDA_vector4f color;

	Float32 uvX;
	Float32 uvY;

} FE_Vertex3D;

typedef struct FE_Mesh
{
	FE_List(Uint32) indices;
	FE_List(FE_Vertex3D) vertices;
} FE_Mesh;