#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanfeQueueFamilyIndices
{
	FE_Optional(Uint32) graphicsFamily;
	FE_Optional(Uint32) presentFamily;
} VulkanfeQueueFamilyIndices;

//Physical device and family queue
Bool FE_API VulkanIsQueueFamilyIndicesCompleted(VulkanfeQueueFamilyIndices* vkQueueFamilyIndices);

void FE_API VulkanInitDefaultDeviceSelection(struct VulkanfeInfo* vkInfo);
void FE_API VulkanPickPhysicalDevice(struct VulkanfeInfo* vkInfo);
Bool FE_API VulkanIsPhysicalDeviceSuitable(const struct VulkanfeInfo* vkInfo, VkPhysicalDevice device);
Bool FE_API VulkanCheckDeviceExtensionSupport(const struct VulkanfeInfo* vkInfo, VkPhysicalDevice device);

VulkanfeQueueFamilyIndices FE_API VulkanFindQueueFamilies(const struct VulkanfeInfo* vkInfo, VkPhysicalDevice device);

//Logical device
void FE_API VulkanCreateLogicalDevice(struct VulkanfeInfo* vkInfo);