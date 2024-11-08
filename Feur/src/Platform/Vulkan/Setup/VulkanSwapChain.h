#pragma once
#include <vulkan/vulkan.h>

typedef struct VulkanfeSwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    FE_List(VkSurfaceFormatKHR) formats;
    FE_List(VkPresentModeKHR) presentModes;
} VulkanfeSwapChainSupportDetails;

void FE_API VulkanCreateSwapChain(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanDestroySwapChain(struct FE_VulkanInfo* vkInfo);

// "VulkanfeSwapChainSupportDetails" must be cleared using "VulkanClearSwapChainSupport" function
VulkanfeSwapChainSupportDetails FE_API VulkanQuerySwapChainSupport(const struct FE_VulkanInfo* vkInfo, VkPhysicalDevice device);
void FE_API VulkanClearSwapChainSupport(VulkanfeSwapChainSupportDetails* vkSwapChainSupportDetails);
VkSurfaceFormatKHR FE_API VulkanChooseSwapSurfaceFormat(const void* feListAvailableFormats);
VkPresentModeKHR FE_API VulkanChooseSwapPresentMode(const void* feListAvailablePresentModes);
VkExtent2D FE_API VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);