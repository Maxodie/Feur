#pragma once
#include <vulkan/vulkan.h>

struct FE_VulkanInfo;

void VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, struct FE_VulkanInfo* vkInfo);
void VulkanCreateDebugMessenger(struct FE_VulkanInfo* vkInfo);
void VulkanCleanupDebugMessenger(struct FE_VulkanInfo* vkInfo);
