#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

void VulkanInitImageViewsDefaultData(FE_VulkanInfo* vkInfo)
{
	FE_ListInit(vkInfo->swapChain.imageViews);
	FE_ListResize(vkInfo->swapChain.imageViews, vkInfo->swapChain.images.impl.count);

}

void VulkanShutdownImageViewsDefaultData(FE_VulkanInfo* vkInfo)
{
	FE_ListClear(vkInfo->swapChain.imageViews);
}

void VulkanCreateImageView(FE_VulkanInfo* vkInfo)
{
	VkImageViewCreateInfo createInfo = { 
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = vkInfo->swapChain.imageFormat,
		.subresourceRange.baseMipLevel = 0,
		.subresourceRange.levelCount = 1,
		.subresourceRange.baseArrayLayer = 0,
		.subresourceRange.layerCount = 1,
		.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	};
	for (size_t i = 0; i < vkInfo->swapChain.images.impl.count; i++)
	{
		createInfo.image = vkInfo->swapChain.images.data[i];

		VkResult result = vkCreateImageView(vkInfo->logicalDevice, &createInfo, NULL, &vkInfo->swapChain.imageViews.data[i]);
		FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create image view ! - %d", result);
	}
}

void VulkanDestroyImageView(FE_VulkanInfo* vkInfo)
{
	for (SizeT i = 0; i < vkInfo->swapChain.imageViews.impl.count; i++)
	{
		vkDestroyImageView(vkInfo->logicalDevice, vkInfo->swapChain.imageViews.data[i], NULL);
	}
}
