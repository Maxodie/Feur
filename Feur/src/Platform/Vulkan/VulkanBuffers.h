#pragma once
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

static void VulkanCreateBuffer(struct FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage, struct FE_VulkanAllocatedBuffer* outAllocatedBuffer);
void VulkanDestroyBuffer(struct FE_VulkanInfo* vkInfo, const struct FE_VulkanAllocatedBuffer* buffer);

void VulkanCreateVertexBuffer(struct FE_VulkanInfo* vkInfo, Uint32 vertexCount);
void VulkanAddVertexIntoBuffer(struct FE_VulkanInfo* vkInfo, FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset);
void VulkanCreateIndexBuffer(struct FE_VulkanInfo* vkInfo, Uint32 indexCount);
void VulkanAddIndexIntoBuffer(struct FE_VulkanInfo* vkInfo, Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset);
void VulkanCreateUniformBuffer(struct FE_VulkanInfo* vkInfo);
void VulkanCreateDrawIndexedIndirectCommandsBuffer(struct FE_VulkanInfo* vkInfo);
void VulkanAddDrawIndexedIndirectCommandsBuffer(struct FE_VulkanInfo* vkInfo, Uint32 indexCount);


void VulkanUpdateUniformBuffer(struct FE_VulkanInfo* vkInfo, const FE_Camera3D * cam);
void VulkanBindBuffers(struct FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer);

void VulkanCopyBuffer(struct FE_VulkanInfo* vkInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);