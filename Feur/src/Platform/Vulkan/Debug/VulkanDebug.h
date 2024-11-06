#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanFeurDebugger 
{
	VkDebugUtilsMessengerEXT callback;
	Bool enableFullVulkanDebugMsg;
} VulkanfeDebugger;

void FE_API VulkanInitDefaultDebug(VulkanfeDebugger* vkfeDebugger);
void FE_API VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, struct VulkanfeInfo* vkInfo);
void FE_API VulkanSetupDebugMessenger(struct VulkanfeInfo* vkInfo);
void FE_API VulkanDestroyDebugMessenger(struct VulkanfeInfo* vkInfo);