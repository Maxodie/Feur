#pragma once

typedef struct FE_BufferAPI
{
	void (*CreateVertexBuffer)(Uint32 vertexCount);
	void (*AddVertexIntoBuffer)(FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset);
	void (*CreateIndexBuffer)(Uint32 indexCount);
	void (*AddIndexIntoBuffer)(Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset);

	void (*DestroyVertexBuffer)();
	void (*DestroyIndexBuffer)();
} FE_BufferAPI;