#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

void FE_API VulkanCreateImageView(VulkanfeInfo* vkInfo)
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

		if (vkCreateImageView(vkInfo->device, &createInfo, NULL, &vkInfo->swapChainImageViews.data[i]) != VK_SUCCESS) {
			FE_CORE_ASSERT(FALSE, "failed to create image view !");
		}
	}
}
