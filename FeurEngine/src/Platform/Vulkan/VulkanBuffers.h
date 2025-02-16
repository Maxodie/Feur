#pragma once
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

struct FE_VulkanInfo;
struct FE_VulkanAllocatedBuffer;

static void VulkanCreateBuffer(struct FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage, struct FE_VulkanAllocatedBuffer* outAllocatedBuffer);
void VulkanDestroyBuffer(struct FE_VulkanInfo* vkInfo, struct FE_VulkanAllocatedBuffer* buffer);

struct FE_VulkanAllocatedBuffer* VulkanCreateVertexBuffer(struct FE_VulkanInfo* vkInfo, Uint32 vertexCount, SizeT* outVertexBufferId);
void VulkanAddVertexIntoBuffer(struct FE_VulkanInfo* vkInfo, FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset, struct FE_VulkanAllocatedBuffer* allocatedVertexBuffer);
struct FE_VulkanAllocatedBuffer* VulkanCreateIndexBuffer(struct FE_VulkanInfo* vkInfo, Uint32 indexCount, SizeT* outIndexBufferId);
void VulkanAddIndexIntoBuffer(struct FE_VulkanInfo* vkInfo, Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset, struct FE_VulkanAllocatedBuffer* allocatedVertexBuffer);
void VulkanCreateUniformBuffer(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyUniformBuffer(struct FE_VulkanInfo* vkInfo);
void VulkanCreateDrawIndexedIndirectCommandsBuffer(struct FE_VulkanInfo* vkInfo);
void VulkanAddDrawIndexedIndirectCommandsBuffer(struct FE_VulkanInfo* vkInfo, Uint32 indexCount, SizeT indexBufferId);


void VulkanUpdateUniformBuffer(struct FE_VulkanInfo* vkInfo, const FE_Camera3D * cam);
void VulkanBindBuffers(struct FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer, SizeT indexBufferId, SizeT vertexBufferId);

void VulkanCopyBuffer(struct FE_VulkanInfo* vkInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
