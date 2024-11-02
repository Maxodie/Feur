#pragma once
#include <vulkan/vulkan.h>
#include "Platform/Vulkan/Debug/VulkanDebug.h"

typedef struct VulkanInfo 
{
	VkInstance vkInstance;
	Bool enableValidationLayers;
	VulkanFeurDebugger vkfeDebugger;

	FE_List(const char* const) validationLayers;

} VulkanInfo;

Bool FE_API CreateVulkanInstance(VulkanInfo* vkInfo);
void FE_API VulkanCleanup(VkInstance vkInstance);