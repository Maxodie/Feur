#pragma once
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

void InitVulkan_VertexArrayBuffer();

struct FE_VulkanAllocatedBuffer VulkanCreateBuffer(struct FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage);
void VulkanDestroyBuffer(struct FE_VulkanInfo* vkInfo, const struct FE_VulkanAllocatedBuffer* buffer);

void VulkanBindMeshBuffer(struct FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer, struct FE_VulkanAllocatedBuffer* verticesBuffer, struct FE_VulkanAllocatedBuffer* indicesBuffer, const FE_Mesh* mesh);

void VulkanCopyBuffer(struct FE_VulkanInfo* vkInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);