#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanfeSwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    FE_List(VkSurfaceFormatKHR) formats;
    FE_List(VkPresentModeKHR) presentModes;
} VulkanfeSwapChainSupportDetails;

void VulkanCreateSwapChain(struct VulkanfeInfo* vkInfo);

VulkanfeSwapChainSupportDetails VulkanQuerySwapChainSupport(const struct VulkanfeInfo* vkInfo, VkPhysicalDevice device);
VkSurfaceFormatKHR VulkanChooseSwapSurfaceFormat(const void* feListAvailableFormats);
VkPresentModeKHR VulkanChooseSwapPresentMode(const void* feListAvailablePresentModes);
VkExtent2D VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);