#include "fepch.h"
#include "Feur/Renderer/Renderer3D.h"
#include "Feur/Renderer/RenderCommand.h"

#define FE_MAX_3D_Indices 100000
#define FE_MAX_3D_Vertices 150000

struct Renderer3DData
{
	const SizeT maxVertices;
	const SizeT maxIndices;
	Uint32 meshIndexOffset;

	SizeT meshVertexBufferCount;
	FE_Vertex3D* meshVertexBufferBase;
	FE_Vertex3D* meshVertexPtr;
	void* apiVertexBuffer;

	SizeT meshIndexBufferCount;
	Uint32* meshIndexBufferBase;
	Uint32* meshIndexPtr;
	void* apiIndexBuffer;

	Uint32 meshIndexCount;
	SizeT meshIndexBufferId;
	SizeT meshVertexBufferId;
	Uint32 meshVertexCount;

} renderer3DData = {
	.maxVertices = FE_MAX_3D_Vertices,
	.maxIndices = FE_MAX_3D_Indices,
	.meshVertexBufferCount = 0,
	.meshVertexBufferBase = { 0 },
	.meshVertexPtr = NULL,
	.apiVertexBuffer = NULL,
	.meshIndexBufferCount = 0,
	.meshIndexBufferBase = { 0 },
	.meshIndexPtr = NULL,
	.apiIndexBuffer = NULL,
	.meshIndexCount = 0,
	.meshIndexOffset = 0,
	.meshIndexBufferId = 0,
	.meshVertexBufferId = 0,
	.meshVertexCount = 0,
};

void FE_DECL FE_Renderer3DInit()
{
	renderer3DData.meshVertexBufferBase = FE_MemoryGeneralAlloc(renderer3DData.maxVertices * sizeof(FE_Vertex3D));
	renderer3DData.meshVertexPtr = renderer3DData.meshVertexBufferBase;
	renderer3DData.meshVertexBufferCount = 1;

	renderer3DData.meshIndexBufferBase = FE_MemoryGeneralAlloc(renderer3DData.maxIndices * sizeof(Uint32));
	renderer3DData.meshIndexPtr = renderer3DData.meshIndexBufferBase;
	renderer3DData.meshIndexBufferCount = 1;

	renderer3DData.apiIndexBuffer = GetRendererAPI()->bufferAPI.CreateIndexBuffer((Uint32)renderer3DData.maxIndices, &renderer3DData.meshIndexBufferId);
	renderer3DData.apiVertexBuffer = GetRendererAPI()->bufferAPI.CreateVertexBuffer((Uint32)renderer3DData.maxVertices, &renderer3DData.meshVertexBufferId);
}

void FE_DECL FE_Renderer3DShutdown()
{
	GetRendererAPI()->bufferAPI.DestroyVertexBuffer(renderer3DData.apiVertexBuffer);
	GetRendererAPI()->bufferAPI.DestroyIndexBuffer(renderer3DData.apiIndexBuffer);

	FE_MemoryGeneralFree(renderer3DData.meshVertexBufferBase);
	FE_MemoryGeneralFree(renderer3DData.meshIndexBufferBase);
}

void FE_DECL FE_Renderer3DBeginScene(const FE_Camera3D* cam)
{
	RenderCommandBeginScene(cam);
}

void FE_DECL FE_Renderer3DEndScene()
{
	FE_Renderer3DDraw();
	RenderCommandEndScene();
}

void FE_DECL FE_Renderer3DDraw()
{
	if (renderer3DData.meshVertexCount)
	{
		GetRendererAPI()->bufferAPI.AddVertexIntoBuffer(renderer3DData.meshVertexBufferBase, renderer3DData.meshVertexCount, 0, renderer3DData.apiVertexBuffer);

		GetRendererAPI()->bufferAPI.AddIndexIntoBuffer(renderer3DData.meshIndexBufferBase, renderer3DData.meshIndexCount, 0, renderer3DData.apiIndexBuffer);

		RenderCommandDrawIndex(renderer3DData.meshIndexCount, renderer3DData.meshIndexBufferId, renderer3DData.meshVertexBufferId);
	}
}

void FE_DECL FE_Renderer3DReset()
{
	renderer3DData.meshVertexPtr = renderer3DData.meshVertexBufferBase;
	renderer3DData.meshIndexPtr = renderer3DData.meshIndexBufferBase;
	renderer3DData.meshIndexCount = 0;
	renderer3DData.meshVertexCount = 0;
	renderer3DData.meshIndexOffset = 0;
}

void FE_DECL FE_Renderer3DResizeVertexBuffer(SizeT bufferCountToAdd)
{
	UintptrT count = renderer3DData.meshVertexPtr - renderer3DData.meshVertexBufferBase;
	renderer3DData.meshVertexBufferCount += bufferCountToAdd;
	renderer3DData.meshVertexBufferBase = FE_MemoryGeneralRealloc(renderer3DData.meshVertexBufferBase, renderer3DData.meshVertexBufferCount * renderer3DData.maxVertices * sizeof(FE_Vertex3D));
	renderer3DData.meshVertexPtr = renderer3DData.meshVertexBufferBase + count;

	GetRendererAPI()->bufferAPI.DestroyVertexBuffer(renderer3DData.apiVertexBuffer);

	renderer3DData.apiVertexBuffer = GetRendererAPI()->bufferAPI.CreateVertexBuffer((Uint32)(renderer3DData.maxVertices * renderer3DData.meshVertexBufferCount), &renderer3DData.meshVertexBufferId);
}

void FE_DECL FE_Renderer3DResizeIndexBuffer(SizeT bufferCountToAdd)
{
	UintptrT count = renderer3DData.meshIndexPtr - renderer3DData.meshIndexBufferBase;
	renderer3DData.meshIndexBufferCount += bufferCountToAdd;
	renderer3DData.meshIndexBufferBase = FE_MemoryGeneralRealloc(renderer3DData.meshIndexBufferBase, renderer3DData.meshIndexBufferCount * renderer3DData.maxIndices * sizeof(Uint32));
	renderer3DData.meshIndexPtr = renderer3DData.meshIndexBufferBase + count;

	GetRendererAPI()->bufferAPI.DestroyIndexBuffer(renderer3DData.apiIndexBuffer);
	
	renderer3DData.apiIndexBuffer = GetRendererAPI()->bufferAPI.CreateIndexBuffer((Uint32)(renderer3DData.maxIndices * renderer3DData.meshIndexBufferCount), &renderer3DData.meshIndexBufferId);
}

Uint32 FE_DECL FE_Renderer3DGetIndexCount()
{
	return renderer3DData.meshIndexCount;
}

SizeT FE_DECL FE_Renderer3DGetVertexCount()
{
	return renderer3DData.meshVertexPtr - renderer3DData.meshVertexBufferBase;
}

SizeT FE_DECL FE_Renderer3DGetVertexBufferCount()
{
	return renderer3DData.meshVertexBufferCount;
}

void FE_DECL FE_Renderer3DDrawMesh(const FE_Mesh* mesh, const FE_CompTransform3D* tr3D)
{
	SizeT currentVerticesCount = mesh->vertices.impl.count + renderer3DData.meshVertexCount;
	if (currentVerticesCount > renderer3DData.maxVertices * renderer3DData.meshVertexBufferCount)
	{
		SizeT count = (currentVerticesCount - renderer3DData.maxVertices * renderer3DData.meshVertexBufferCount) / renderer3DData.maxVertices;
		FE_Renderer3DResizeVertexBuffer(count + 1);
	}

	SizeT currentIndicesCount = mesh->indices.impl.count + renderer3DData.meshIndexCount;
	if (currentIndicesCount > renderer3DData.maxIndices * renderer3DData.meshIndexBufferCount)
	{
		SizeT count = (currentIndicesCount - renderer3DData.maxIndices * renderer3DData.meshIndexBufferCount) / renderer3DData.maxIndices;
		FE_Renderer3DResizeIndexBuffer(count + 1);
	}

	ILDA_matrix4x4 transform = ILDA_translation(&ILDA_matrix4x4_identity, &tr3D->position);
	ILDA_matrix4x4 scale = ILDA_matrix4x4_identity;

	ILDA_scale(&scale, &tr3D->scale);
	ILDA_matrix4x4_mul_same(&transform, &scale);
	ILDA_vector4f transformPos;
	ILDA_vector4f vertexPos;

	renderer3DData.meshVertexCount += mesh->vertices.impl.count;
	SizeT i = 0;
	for (i = 0; i < mesh->vertices.impl.count; i++)
	{
		vertexPos = (ILDA_vector4f){ .x = mesh->vertices.data[i].position.x, .y = mesh->vertices.data[i].position.y, .z = mesh->vertices.data[i].position.z, 1 };
		transformPos = ILDA_matrix4x4_mul_vector(&transform, &vertexPos);
		*renderer3DData.meshVertexPtr = mesh->vertices.data[i];
		renderer3DData.meshVertexPtr->position = (ILDA_vector3f){ .x = transformPos.x, .y = transformPos.y, .z = transformPos.z };
		renderer3DData.meshVertexPtr++;
	}

	renderer3DData.meshIndexCount += mesh->indices.impl.count;
	Uint32 indexOffset = 0;
	Uint32 currentIndex = 0;
	for (i = 0; i < mesh->indices.impl.count; i++)
	{
		currentIndex = mesh->indices.data[i];
		*renderer3DData.meshIndexPtr = renderer3DData.meshIndexOffset + currentIndex;
		renderer3DData.meshIndexPtr++;

		if (currentIndex > indexOffset)
		{
			indexOffset = currentIndex;
		}
	}
	renderer3DData.meshIndexOffset += indexOffset + 1;
}

void FE_DECL FE_Renderer3DDrawModel(const FE_Model3D* model, const FE_CompTransform3D* tr3D)
{
	for (SizeT i = 0; i < model->meshes.impl.count; i++)
	{
		FE_Renderer3DDrawMesh(&model->meshes.data[i], tr3D);
	}
}
