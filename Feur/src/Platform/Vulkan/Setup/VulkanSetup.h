#pragma once
#include <vulkan/vulkan.h>
#include "Platform/Vulkan/Debug/VulkanDebug.h"

typedef struct VulkanfeInfo 
{
	VkInstance vkInstance;
	VulkanfeDebugger vkfeDebugger;
	FE_List(const char*) validationLayers;
	FE_List(const char*) deviceExtensions;

	VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSurfaceKHR surface;


	//temp
	VkSwapchainKHR swapChain;
	FE_List(VkImage) swapChainImages;
	FE_List(VkImageView) swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	Bool enableValidationLayers;

} VulkanfeInfo;

void FE_API CreateVulkanInstance(VulkanfeInfo* vkInfo);
void FE_API CreateVulkanSurface(VulkanfeInfo* vkInfo);
void FE_API VulkanCleanup(VulkanfeInfo* vkInfo);