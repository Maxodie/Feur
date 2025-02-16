#pragma once
#include <vulkan/vulkan.h>

struct FE_VulkanInfo;
struct FE_VulkanQueueFamilyIndices;

//Physical device and family queue
Bool VulkanIsQueueFamilyIndicesCompleted(struct FE_VulkanQueueFamilyIndices* vkQueueFamilyIndices);

void VulkanInitDefaultDeviceSelection(struct FE_VulkanInfo* vkInfo);
void VulkanPickPhysicalDevice(struct FE_VulkanInfo* vkInfo);
Bool VulkanTryLoadingPhysicalDevice(struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

void VulkanLoadQueueFamilies(struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);

//Logical device
void VulkanCreateLogicalDevice(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyLogicalDevice(struct FE_VulkanInfo* vkInfo);
