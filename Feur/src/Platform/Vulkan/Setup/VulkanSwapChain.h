#pragma once
#include <vulkan/vulkan.h>

void VulkanCreateSwapChain(struct FE_VulkanInfo* vkInfo);
void VulkanDestroySwapChain(struct FE_VulkanInfo* vkInfo);

void VulkanInitSwapChainImages(struct FE_VulkanInfo* vkInfo);
void VulkanShutdownSwapChainImages(struct FE_VulkanInfo* vkInfo);

void VulkanSwapChainImagesQuery(struct FE_VulkanInfo* vkInfo);

// "VulkanfeSwapChainSupportDetails" must be cleared using "VulkanClearSwapChainSupport" function
void VulkanInitSwapChainSupportData(struct FE_VulkanInfo* vkInfo);
void VulkanShutdownSwapChainSupportData(struct FE_VulkanInfo* vkInfo);
Bool VulkanSwapChainSupportByQuery(struct FE_VulkanInfo* vkInfo);
VkSurfaceFormatKHR VulkanChooseSwapSurfaceFormat(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailableFormats);
VkPresentModeKHR VulkanChooseSwapPresentMode(FE_ListParameterPtr(VkSurfaceFormatKHR) pAvailablePresentModes);
VkExtent2D VulkanChooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);

void VulkanResizeSwapChain(struct FE_VulkanInfo* vkInfo, Uint32 width, Uint32 height);