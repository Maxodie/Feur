#pragma once
#include <vulkan/vulkan.h>

void VulkanInitSwapChain(struct FE_VulkanInfo* vkInfo);
void VulkanCreateSwapChain(struct FE_VulkanInfo* vkInfo);
void VulkanCreateSwapChainImages(struct FE_VulkanInfo* vkInfo);
void VulkanDestroySwapChain(struct FE_VulkanInfo* vkInfo);
void VulkanShutdownSwapChain(struct FE_VulkanInfo* vkInfo);

// "VulkanfeSwapChainSupportDetails" must be cleared using "VulkanClearSwapChainSupport" function
Bool VulkanCreateSwapChainSupportByQuery(struct FE_VulkanInfo* vkInfo);
void VulkanClearSwapChainSupport(struct FE_VulkanInfo* vkInfo);
VkSurfaceFormatKHR VulkanChooseSwapSurfaceFormat(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailableFormats);
VkPresentModeKHR VulkanChooseSwapPresentMode(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailablePresentModes);
VkExtent2D VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);

void VulkanResizeSwapChain(struct FE_VulkanInfo* vkInfo, Uint32 width, Uint32 height);