#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanFeurDebugger 
{
	Bool enableFullVulkanDebugMsg;
	VkDebugUtilsMessengerEXT callback;
} VulkanFeurDebugger;

void FE_API VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, struct VulkanInfo* vkInfo);
void FE_API VulkanSetupDebugMessenger(struct VulkanInfo* vkInfo);
void FE_API VulkanDestroyDebugMessenger(struct VulkanInfo* vkInfo);