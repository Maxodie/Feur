#pragma once
#include <vulkan/vulkan.h>

struct FE_VulkanInfo;

void VulkanCreateGraphicsPipeline(struct FE_VulkanInfo* vkInfo, const char* vertexShaderPath, const char* fragmentShaderPath);
void VulkanDestoryGraphicsPipeline(struct FE_VulkanInfo* vkInfo);

void VulkanGraphicsPipelineBind(VkCommandBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline);

void VulkanCreateDescriptorSetLayout(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyDescriptionSetLayout(struct FE_VulkanInfo* vkInfo);

void VulkanCreateDescriptorPool(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyDescriptorPool(struct FE_VulkanInfo* vkInfo);

void VulkanCreateDescriptorSets(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyDescriptorSets(struct FE_VulkanInfo* vkInfo);
