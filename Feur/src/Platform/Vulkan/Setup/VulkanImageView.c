#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

void FE_API VulkanCreateImageView(FE_VulkanInfo* vkInfo)
{
	FE_ListInit(vkInfo->swapChainImageViews);
	FE_ListResize(vkInfo->swapChainImageViews, vkInfo->swapChainImages.impl.count);

	for (size_t i = 0; i < vkInfo->swapChainImages.impl.count; i++)
	{
		VkImageViewCreateInfo createInfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = vkInfo->swapChainImages.data[i],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = vkInfo->swapChainImageFormat,
			.components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
			.components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
			.components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
			.components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
			.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.subresourceRange.baseMipLevel = 0,
			.subresourceRange.levelCount = 1,
			.subresourceRange.baseArrayLayer = 0,
			.subresourceRange.layerCount = 1,
		};

		VkResult result = vkCreateImageView(vkInfo->device, &createInfo, NULL, &vkInfo->swapChainImageViews.data[i]);
		FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create image view ! - %d", result);
	}
}

void FE_API VulkanDestroyImageView(FE_VulkanInfo* vkInfo)
{
	for (SizeT i = 0; i < vkInfo->swapChainImageViews.impl.count; i++)
	{
		vkDestroyImageView(vkInfo->device, vkInfo->swapChainImageViews.data[i], NULL);
	}

	FE_ListClear(vkInfo->swapChainImageViews);
}
