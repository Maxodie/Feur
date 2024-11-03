#pragma once
#include <vulkan/vulkan.h>
#include "Platform/Vulkan/Debug/VulkanDebug.h"

typedef struct VulkanfeInfo 
{
	VkInstance vkInstance;
	VulkanFeurDebugger vkfeDebugger;
	FE_List(const char*) validationLayers;

	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;

	Bool enableValidationLayers;

} VulkanfeInfo;

Bool FE_API CreateVulkanInstance(VulkanfeInfo* vkInfo);
void FE_API VulkanCleanup(VulkanfeInfo* vkInfo);