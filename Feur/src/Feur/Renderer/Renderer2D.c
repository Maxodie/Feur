#include "fepch.h"
#include "Feur/Renderer/Renderer2D.h"
#include "Feur/Renderer/RenderCommand.h"

#define FE_MAX_2D_QUAD 5

struct Renderer2DData
{
	const Uint32 maxVertices;
	const Uint32 maxIndices;
	Uint32 quadIndexOffset;

	SizeT quadVertexBufferCount;
	FE_Vertex3D* quadVertexBufferBase;
	FE_Vertex3D* quadVertexPtr;

	ILDA_vector4f quadVertexPos[4];
	ILDA_vector2f quadTexCoords[4];

	SizeT quadIndexBufferCount;
	Uint32* quadIndexBufferBase;
	Uint32* quadIndexPtr;

	Uint32 quadIndexCount;

} renderer2DData = {
	.maxVertices = FE_MAX_2D_QUAD * 4,
	.maxIndices = FE_MAX_2D_QUAD * 6,
	.quadVertexBufferCount = 0,
	.quadVertexBufferBase = { 0 },
	.quadVertexPtr = NULL,
	.quadIndexBufferCount = 0,
	.quadIndexBufferBase = { 0 },
	.quadIndexPtr = NULL,
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
	renderer2DData.quadVertexBufferBase = FE_MemoryGeneralAlloc(renderer2DData.maxVertices * sizeof(FE_Vertex3D));
	renderer2DData.quadVertexPtr = renderer2DData.quadVertexBufferBase;
	renderer2DData.quadVertexBufferCount = 1;
	
	renderer2DData.quadIndexBufferBase = FE_MemoryGeneralAlloc(renderer2DData.maxIndices * sizeof(Uint32));
	renderer2DData.quadIndexPtr = renderer2DData.quadIndexBufferBase;
	renderer2DData.quadIndexBufferCount = 1;

	GetRendererAPI()->bufferAPI.CreateVertexBuffer(renderer2DData.maxVertices);
	GetRendererAPI()->bufferAPI.CreateIndexBuffer(renderer2DData.maxIndices);
}

void FE_DECL FE_Renderer2DShutdown()
{
	GetRendererAPI()->bufferAPI.DestroyVertexBuffer();
	GetRendererAPI()->bufferAPI.DestroyIndexBuffer();

	FE_MemoryGeneralFree(renderer2DData.quadVertexBufferBase);
	FE_MemoryGeneralFree(renderer2DData.quadIndexBufferBase);
}

void FE_DECL FE_Renderer2DBeginScene(const FE_Camera3D* cam)
{
	RenderCommandBeginScene(cam);
}

void FE_DECL FE_Renderer2DEndScene()
{
	FE_Renderer2DDraw();
	RenderCommandEndScene();
}

void FE_DECL FE_Renderer2DDraw()
{
	Uint32 dataSize = (Uint32)(renderer2DData.quadVertexPtr - renderer2DData.quadVertexBufferBase);
	if (dataSize > 0)
	{
		GetRendererAPI()->bufferAPI.AddVertexIntoBuffer(renderer2DData.quadVertexBufferBase, dataSize, 0);

		GetRendererAPI()->bufferAPI.AddIndexIntoBuffer(renderer2DData.quadIndexBufferBase, renderer2DData.quadIndexCount, 0);

		RenderCommandDrawIndex(renderer2DData.quadIndexCount);
	}
}

void FE_DECL FE_Renderer2DReset()
{
	renderer2DData.quadVertexPtr = renderer2DData.quadVertexBufferBase;
	renderer2DData.quadIndexPtr = renderer2DData.quadIndexBufferBase;
	renderer2DData.quadIndexCount = 0;
	renderer2DData.quadIndexOffset = 0;
}

void FE_DECL FE_Renderer2DResizeBuffer(SizeT bufferCountToAdd)
{
	UintptrT count = renderer2DData.quadVertexPtr - renderer2DData.quadVertexBufferBase;
	renderer2DData.quadVertexBufferCount += bufferCountToAdd;
	renderer2DData.quadVertexBufferBase = FE_MemoryGeneralRealloc(renderer2DData.quadVertexBufferBase, renderer2DData.quadVertexBufferCount * renderer2DData.maxVertices * sizeof(FE_Vertex3D));
	renderer2DData.quadVertexPtr = renderer2DData.quadVertexBufferBase + count;

	count = renderer2DData.quadIndexPtr - renderer2DData.quadIndexBufferBase;
	renderer2DData.quadIndexBufferCount += bufferCountToAdd;
	renderer2DData.quadIndexBufferBase = FE_MemoryGeneralRealloc(renderer2DData.quadIndexBufferBase, renderer2DData.quadIndexBufferCount * renderer2DData.maxIndices * sizeof(Uint32));
	renderer2DData.quadIndexPtr = renderer2DData.quadIndexBufferBase + count;

	GetRendererAPI()->bufferAPI.DestroyVertexBuffer();
	GetRendererAPI()->bufferAPI.DestroyIndexBuffer();

	GetRendererAPI()->bufferAPI.CreateVertexBuffer(renderer2DData.maxVertices * renderer2DData.quadVertexBufferCount);
	GetRendererAPI()->bufferAPI.CreateIndexBuffer(renderer2DData.maxIndices * renderer2DData.quadIndexBufferCount);
}

Uint32 FE_DECL FE_Renderer2DGetIndexCount()
{
	return renderer2DData.quadIndexCount;
}

SizeT FE_DECL FE_Renderer2DGetVertexCount()
{
	return renderer2DData.quadVertexPtr - renderer2DData.quadVertexBufferBase;
}

SizeT FE_DECL FE_Renderer2DGetVertexBufferCount()
{
	return renderer2DData.quadVertexBufferCount;
}

void FE_DECL FE_Renderer2DDrawQuad(const ILDA_vector3f* position, const ILDA_vector2f* size, const FE_Color* color)
{
	if ((SizeT)(renderer2DData.quadIndexCount + 6) >= renderer2DData.maxIndices * renderer2DData.quadIndexBufferCount)
	{
		SizeT count = ((SizeT)(renderer2DData.quadIndexCount + 6) - renderer2DData.maxIndices * renderer2DData.quadIndexBufferCount) / renderer2DData.maxIndices;
		FE_Renderer2DResizeBuffer(count ? count : 1);
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
