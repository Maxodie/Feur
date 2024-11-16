#pragma once
#include <vulkan/vulkan.h>

void VulkanCreateGraphicsPipeline(struct FE_VulkanInfo* vkInfo); 
void VulkanDestoryGraphicsPipeline(struct FE_VulkanInfo* vkInfo);

void VulkanGraphicsPipelineBind(VkCommandBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);

void VulkanCreateDescriptorSetLayout(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyDescriptionSetLayout(struct FE_VulkanInfo* vkInfo);

void VulkanCreateDescriptorPool(struct FE_VulkanInfo* vkInfo); 
void VulkanDestroyDescriptorPool(struct FE_VulkanInfo* vkInfo);

void VulkanCreateDescriptorSets(struct FE_VulkanInfo* vkInfo); 
void VulkanDestroyDescriptorSets(struct FE_VulkanInfo* vkInfo);