#pragma once
#include <vulkan/vulkan.h>

//Physical device and family queue
Bool FE_API VulkanIsQueueFamilyIndicesCompleted(struct FE_VulkanQueueFamilyIndices* vkQueueFamilyIndices);

void FE_API VulkanInitDefaultDeviceSelection(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanPickPhysicalDevice(struct FE_VulkanInfo* vkInfo);
Bool FE_API VulkanTryLoadingPhysicalDevice(struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

void FE_API VulkanLoadQueueFamilies(const struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

//Logical device
void FE_API VulkanCreateLogicalDevice(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanDestroyLogicalDevice(struct FE_VulkanInfo* vkInfo);