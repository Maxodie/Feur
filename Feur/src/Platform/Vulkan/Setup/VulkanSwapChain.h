#pragma once
#include <vulkan/vulkan.h>

void FE_API VulkanCreateSwapChain(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanDestroySwapChain(struct FE_VulkanInfo* vkInfo);

// "VulkanfeSwapChainSupportDetails" must be cleared using "VulkanClearSwapChainSupport" function
Bool FE_API VulkanCreateSwapChainSupportByQuery(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanClearSwapChainSupport(struct FE_VulkanInfo* vkInfo);
VkSurfaceFormatKHR FE_API VulkanChooseSwapSurfaceFormat(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailableFormats);
VkPresentModeKHR FE_API VulkanChooseSwapPresentMode(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailablePresentModes);
VkExtent2D FE_API VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);