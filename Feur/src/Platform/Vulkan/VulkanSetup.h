#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanInfo {
	VkInstance vkInstance;
	Bool enableValidationLayers;

	const char* const* validationLayers[1];//remove table to fit wwith the createInfo struct
	Uint32 validationsCount;

} VulkanInfo;

Bool FE_API CreateVulkanInstance(VulkanInfo* vkInfo);
void FE_API VulkanCleanup(VkInstance* vkInstance);