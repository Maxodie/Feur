#pragma once

typedef struct FE_BufferAPI
{
	void* (*CreateVertexBuffer)(Uint32 vertexCount, SizeT* outVertexBufferId);
	void (*AddVertexIntoBuffer)(FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset, void* allocatedBuffer);
	void* (*CreateIndexBuffer)(Uint32 indexCount, SizeT* outIndexBufferId);//add outindexbufferid
	void (*AddIndexIntoBuffer)(Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset, void* allocatedBuffer);

	void (*DestroyVertexBuffer)(void* allocatedBuffer);
	void (*DestroyIndexBuffer)(void* allocatedBuffer);
} FE_BufferAPI;