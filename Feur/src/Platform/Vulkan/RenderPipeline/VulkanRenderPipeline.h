#pragma once
#include <vulkan/vulkan.h>

void VulkanCreateGraphicsPipeline(struct FE_VulkanInfo* vkInfo); 
void VulkanCleanupGraphicsPipeline(struct FE_VulkanInfo* vkInfo);

void VulkanGraphicsPipelineBind(VkCommandBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);