#pragma once
#include <vulkan/vulkan.h>

void FE_API VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, struct FE_VulkanInfo* vkInfo);
void FE_API VulkanCreateDebugMessenger(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanCleanupDebugMessenger(struct FE_VulkanInfo* vkInfo);