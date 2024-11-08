#pragma once
#include <vulkan/vulkan.h>

//Physical device and family queue
Bool FE_API VulkanIsQueueFamilyIndicesCompleted(struct FE_VulkanQueueFamilyIndices* vkQueueFamilyIndices);

void FE_API VulkanInitDefaultDeviceSelection(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanPickPhysicalDevice(struct FE_VulkanInfo* vkInfo);
Bool FE_API VulkanSelectPhysicalDevice(struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

struct FE_VulkanQueueFamilyIndices FE_API VulkanFindQueueFamilies(const struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

//Logical device
void FE_API VulkanCreateLogicalDevice(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanDestroyLogicalDevice(struct FE_VulkanInfo* vkInfo);