#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanInfo {
	VkInstance vkInstance;
	BOOL enableValidationLayers;

	const char* const* validationLayers[1];
	size_t validationsCount;

} VulkanInfo;

BOOL FE_API CreateVulkanInstance(VulkanInfo* vkInfo);
void FE_API VulkanCleanup(VkInstance* vkInstance);