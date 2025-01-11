#include "fepch.h"
#include "Feur/Renderer/Renderer2D.h"
#include "Feur/Renderer/RenderCommand.h"

struct Renderer2DData
{
	const Uint32 maxQuads;
	const Uint32 maxVertices;
	const Uint32 maxIndices;
	Uint32 quadIndexOffset;

	FE_Vertex3D* quadVertexPtr;
	FE_Vertex3D* quadVertexPtrBase;

	ILDA_vector4f quadVertexPos[4];
	ILDA_vector2f quadTexCoords[4];

	Uint32* quadIndexPtr;
	Uint32* quadIndexPtrBase;

	Uint32 quadIndexCount;

} renderer2DData = {
	.maxQuads = 1000,
	.maxVertices = 1000 * 4,
	.maxIndices = 1000 * 6,
	.quadVertexPtr = NULL,
	.quadVertexPtrBase = NULL,
	.quadIndexPtr = NULL,
	.quadIndexPtrBase = NULL,
	.quadVertexPos = {
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{ 0.5f, -0.5f, 0.0f, 1.0f},
		{ 0.5f,  0.5f, 0.0f, 1.0f},
		{-0.5f,  0.5f, 0.0f, 1.0f},
	},
	.quadTexCoords = {
		{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
	},
	.quadIndexCount = 0,
	.quadIndexOffset = 0,
};

void FE_DECL FE_Renderer2DInit()
{
	renderer2DData.quadVertexPtrBase = FE_MemoryGeneralAlloc(renderer2DData.maxVertices);
	renderer2DData.quadVertexPtr = renderer2DData.quadVertexPtrBase;

	renderer2DData.quadIndexPtrBase = FE_MemoryGeneralAlloc(renderer2DData.maxIndices);
	renderer2DData.quadIndexPtr = renderer2DData.quadIndexPtrBase;

	GetRendererAPI()->bufferAPI.CreateVertexBuffer(renderer2DData.maxVertices);
	GetRendererAPI()->bufferAPI.CreateIndexBuffer(renderer2DData.maxIndices);
}

void FE_DECL FE_Renderer2DShutdown()
{
	FE_MemoryGeneralFree(renderer2DData.quadVertexPtrBase);
	FE_MemoryGeneralFree(renderer2DData.quadIndexPtrBase);
}

void FE_DECL FE_Renderer2DBeginScene(const FE_Camera3D* cam)
{
	RenderCommandBeginScene(cam);
}

void FE_DECL FE_Renderer2DEndScene()
{
	FE_Renderer2DDraw();
}

void FE_DECL FE_Renderer2DDraw()
{
	Uint32 dataSize = (Uint32)(renderer2DData.quadVertexPtr - renderer2DData.quadVertexPtrBase);
	if (dataSize > 0)
	{
		GetRendererAPI()->bufferAPI.AddVertexIntoBuffer(renderer2DData.quadVertexPtrBase, dataSize, 0);

		GetRendererAPI()->bufferAPI.AddIndexIntoBuffer(renderer2DData.quadIndexPtrBase, renderer2DData.quadIndexCount, 0);


		RenderCommandEndScene();

		RenderCommandDrawIndex(renderer2DData.quadIndexCount);
	}
}

void FE_DECL FE_Renderer2DReset()
{
	renderer2DData.quadVertexPtr = renderer2DData.quadVertexPtrBase;
	renderer2DData.quadIndexPtr = renderer2DData.quadIndexPtrBase;
	renderer2DData.quadIndexCount = 0;
	renderer2DData.quadIndexOffset = 0;
}

void FE_DECL FE_Renderer2DCreateTemporaryBuffer()
{

}

Uint32 FE_DECL FE_Renderer2DGetIndexCount()
{
	return renderer2DData.quadIndexCount;
}

void FE_DECL FE_Renderer2DDrawQuad(const ILDA_vector3f* position, const ILDA_vector2f* size, const FE_Color* color)
{
	// TODO : check index buffer size and reset if needed

	if (renderer2DData.quadIndexCount >= renderer2DData.maxIndices)
	{
		FE_Renderer2DCreateTemporaryBuffer();
	}

	static const Uint8 quadVertexCount = 4;
	static const Uint8 quadIndexCount = 6;

	renderer2DData.quadIndexPtr[0] = renderer2DData.quadIndexOffset;
	renderer2DData.quadIndexPtr[1] = renderer2DData.quadIndexOffset + 1;
	renderer2DData.quadIndexPtr[2] = renderer2DData.quadIndexOffset + 2;
	renderer2DData.quadIndexPtr[3] = renderer2DData.quadIndexOffset + 2;
	renderer2DData.quadIndexPtr[4] = renderer2DData.quadIndexOffset + 3;
	renderer2DData.quadIndexPtr[5] = renderer2DData.quadIndexOffset;
	renderer2DData.quadIndexOffset += 4;

	renderer2DData.quadIndexPtr += quadIndexCount;
	renderer2DData.quadIndexCount += quadIndexCount;

	ILDA_matrix4x4 transform = ILDA_translation(&ILDA_matrix4x4_identity, position);
	ILDA_matrix4x4 scale = ILDA_matrix4x4_identity;

	ILDA_vector3f vec3 = { .x = size->x, .y = size->y, .z = 1.0f };
	ILDA_scale(&scale, &vec3);
	ILDA_matrix4x4_mul_same(&transform, &scale);

	for (Uint8 i = 0; i < quadVertexCount; i++)
	{
		renderer2DData.quadVertexPtr->position = ILDA_matrix4x4_mul_vector(&transform, &renderer2DData.quadVertexPos[i]);
		renderer2DData.quadVertexPtr->color = *color;
		renderer2DData.quadVertexPtr->texCoord = renderer2DData.quadTexCoords[i];
		renderer2DData.quadVertexPtr->normal = (ILDA_vector3f){ 0 };

		renderer2DData.quadVertexPtr ++;
	}
}
