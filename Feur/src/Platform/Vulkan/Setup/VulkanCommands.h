#pragma once
#include <vulkan/vulkan.h>

Bool VulkanCommandBufferAlloc(VkDevice logicalDevice, VkCommandPool cmdPool, Bool isPrimary, VkCommandBuffer* outCmdBuffer); 
void VulkanCommandBufferFree(VkDevice logicalDevice, VkCommandPool cmdPool, VkCommandBuffer* cmdBuffer);

Bool VulkanCommandBufferBegin(VkCommandBuffer cmdBuffer, Bool isSingleUse);
Bool VulkanCommandBufferEnd(VkCommandBuffer cmdBuffer);
Bool VulkanCommandBufferReset(VkCommandBuffer cmdBuffer);

void VulkanCommandBufferAllocAndBeginSingleUse(VkDevice logicalDevice, VkCommandPool pool, VkCommandBuffer* cmdBuffer);
void VulkanCommandBufferEndAndFreeSingleUse(VkDevice logicalDevice, VkCommandPool pool, VkCommandBuffer* cmdBuffer, VkQueue graphicsQueue);

void VulkanCreateCommandPool(struct FE_VulkanInfo* vkInfo); 
void VulkanDestroyCommandPool(struct FE_VulkanInfo* vkInfo);

void VulkanCreateCommandBuffers(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyCommandBuffers(struct FE_VulkanInfo* vkInfo);