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
	ILDA_vector3f position;
	ILDA_vector3f normal;
	FE_Color color;
	ILDA_matrix4x4 transform;
} FE_Vertex3D;

typedef struct FE_UniformBufferObject 
{
	ILDA_matrix4x4 mvp;

	FE_Color ambientLightColor;  // a is intensity
	ILDA_vector3f lightPosition;
	FE_ALIGN_AS(16) FE_Color lightColor;  // a is intensity
} FE_UniformBufferObject;

typedef struct FE_Mesh
{
	FE_List(Uint32) indices;
	FE_List(FE_Vertex3D) vertices;
} FE_Mesh;

typedef struct FE_Model3D
{
	FE_List(FE_Mesh) meshes;
} FE_Model3D;

Bool FE_DECL FE_ModelLoad(const char* path, FE_Model3D* outModel);
void FE_DECL FE_ModelFree(FE_Model3D* outModel);