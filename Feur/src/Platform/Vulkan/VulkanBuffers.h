#pragma once
#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

void InitVulkan_VertexArrayBuffer();

struct FE_VulkanAllocatedBuffer VulkanCreateBuffer(struct FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);
void VulkanDestroyBuffer(struct FE_VulkanInfo* vkInfo, const struct FE_VulkanAllocatedBuffer* buffer);

struct FE_VulkanGPUMeshBuffers VulkanUploadMeshBuffer(struct FE_VulkanInfo* vkInfo, const FE_Mesh* mesh);