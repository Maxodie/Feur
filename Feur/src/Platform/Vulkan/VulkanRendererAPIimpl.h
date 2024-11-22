#pragma once

Bool VulkanInit_impl(RendererAPIData* apiData);

void VulkanFramePrepare_impl();
Bool VulkanFrameCommandListBegin_impl();
void VulkanBeginRendering_impl(FE_Color* clearColor);
void VulkanSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
void VulkanSetScissor_impl(Uint32 width, Uint32 height);
void VulkanBindPipeline_impl();

void VulkanBeginScene_impl(const FE_Camera* cam);
void VulkanEndScene_impl();
void VulkanDrawIndex_impl(Uint32 indexCount);

void VulkanEndRendering_impl();
Bool VulkanFrameCommandListEnd_impl();
Bool VulkanFrameSubmit_impl();
Bool VulkanFramePresent_impl();
void VulkanWaitIdle_impl();
void VulkanShutdown_impl();

void VulkanOnWindowResized_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 drawIndexCount);

Bool CanVulkanContinueRendering();

/*======================== BUFFERS ==============================*/
void VulkanCreateVertexBuffer_impl(Uint32 vertexCount);//add this in a buffer abstraction in buffer.h and use it in renderer2D
void VulkanAddVertexIntoBuffer_impl(FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset);
void VulkanCreateIndexBuffer_impl(Uint32 indexCount);
void VulkanAddIndexIntoBuffer_impl(Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset);