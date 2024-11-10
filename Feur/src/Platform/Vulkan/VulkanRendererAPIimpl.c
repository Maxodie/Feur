#include "fepch.h"
#include "Platform/Vulkan/VulkanRendererAPIimpl.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"
#include "Platform/Vulkan/Setup/VulkanCommands.h"

#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"

#include "Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.h"

static FE_VulkanInfo* vkInfo;

Bool VulkanInit_impl(RendererAPIData* apiData)
{
	vkInfo = FE_MemoryGeneralAlloc(sizeof(FE_VulkanInfo));
	vkInfo->apiData = apiData;

	VulkanInitValidationLayer(&vkInfo->debugger.validationLayer);

	VulkanCreateInstance(vkInfo);

	if (vkInfo->debugger.validationLayer.enableValidationLayers)
	{
		VulkanCreateDebugMessenger(vkInfo);
	}

	CreateVulkanSurface(vkInfo);
	VulkanInitDefaultDeviceSelection(vkInfo);
	VulkanPickPhysicalDevice(vkInfo);
	VulkanCreateLogicalDevice(vkInfo);

	VulkanInitSwapChainSupportData(vkInfo);
	VulkanCreateSwapChain(vkInfo);
	VulkanInitSwapChainImages(vkInfo);

	VulkanInitImageViewsDefaultData(vkInfo);
	VulkanCreateImageView(vkInfo);
	VulkanCreateGraphicsPipeline(vkInfo);

	VulkanCreateCommandPool(vkInfo);
	VulkanCreateCommandBuffers(vkInfo);

	VulkanCreateSemaphoresAndFences(vkInfo);

	apiData->nativeInfoAPI = vkInfo;
	return TRUE;
}

void VulkanFramePrepare_impl()
{
	vkWaitForFences(vkInfo->logicalDevice, 1, &vkInfo->inFlightFences[vkInfo->currentFrame], VK_TRUE, UINT64_MAX);
	vkResetFences(vkInfo->logicalDevice, 1, &vkInfo->inFlightFences[vkInfo->currentFrame]);
	VkResult result = vkAcquireNextImageKHR(
		vkInfo->logicalDevice,
		vkInfo->swapChain.handle,
		UINT64_MAX,
		vkInfo->imageAvailableSemaphores[vkInfo->currentFrame],
		VK_NULL_HANDLE,
		&vkInfo->imageIndex
	);

	/*if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		VulkanResizeSwapChain(vkInfo, GetApp()->windowData.w, GetApp()->windowData.h);
		return;
	}
	else*/ if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		FE_CORE_LOG_ERROR("failed to prepare the frame : %d", result);
		return;
	}

	VulkanCommandBufferReset(vkInfo->cmdBuffers[vkInfo->currentFrame]);
}

Bool VulkanFrameCommandListBegin_impl()
{
	//if (!CanVulkanContinueRendering()) return FALSE;

	return VulkanCommandBufferBegin(vkInfo->cmdBuffers[vkInfo->currentFrame], FALSE);
}

void VulkanBeginRendering_impl(ILDA_vector4f* clearColor)
{
	//if (!CanVulkanContinueRendering()) return;

	for (SizeT i = 0; i < vkInfo->swapChain.images.impl.count; i++)
	{
		vkInfo->imageBarriers[i].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		vkInfo->imageBarriers[i].pNext = VK_NULL_HANDLE;
		vkInfo->imageBarriers[i].srcAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;
		vkInfo->imageBarriers[i].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
		vkInfo->imageBarriers[i].oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		vkInfo->imageBarriers[i].newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		vkInfo->imageBarriers[i].srcQueueFamilyIndex = 0;
		vkInfo->imageBarriers[i].dstQueueFamilyIndex = 0;
		vkInfo->imageBarriers[i].image = vkInfo->swapChain.images.data[i];
		vkInfo->imageBarriers[i].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		vkInfo->imageBarriers[i].subresourceRange.baseMipLevel = 0;
		vkInfo->imageBarriers[i].subresourceRange.levelCount = 1;
		vkInfo->imageBarriers[i].subresourceRange.baseArrayLayer = 0;
		vkInfo->imageBarriers[i].subresourceRange.layerCount = 1;
	}

	vkCmdPipelineBarrier(
		vkInfo->cmdBuffers[vkInfo->currentFrame], VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE,
		(Uint32)vkInfo->swapChain.images.impl.count, vkInfo->imageBarriers
	);

	VkClearValue clearValue = { .color = {
			.float32[0] = clearColor->x,
			.float32[1] = clearColor->y,
			.float32[2] = clearColor->z,
			.float32[3] = clearColor->w,
		},

		.depthStencil = {
			.depth = 0,
			.stencil = 0,
		},
	};

	VkRenderingAttachmentInfo colorAttachmentInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
		.pNext = VK_NULL_HANDLE,
		.imageView = vkInfo->swapChain.imageViews.data[vkInfo->imageIndex],
		.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		.resolveMode = VK_RESOLVE_MODE_NONE,
		.resolveImageView = VK_NULL_HANDLE,
		.resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.clearValue = clearValue,
	};

	VkRenderingInfo renderingInfo = {
		.sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.renderArea.extent.width = vkInfo->swapChain.extent.width,
		.renderArea.extent.height = vkInfo->swapChain.extent.height,
		.renderArea.offset.x = 0,
		.renderArea.offset.y = 0,
		.layerCount = 1,
		.viewMask = 0,
		.colorAttachmentCount = 1,
		.pColorAttachments = &colorAttachmentInfo
	};

	vkInfo->vkCmdBeginRenderingKHR(vkInfo->cmdBuffers[vkInfo->currentFrame], &renderingInfo);
}

void VulkanSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth)
{
	//if (!CanVulkanContinueRendering()) return;

	VkViewport viewPort = {
		.x = (float)x,
		.y = (float)y,
		.width = (float)width,
		.height = (float)height,
		.minDepth = (float)minDepth,
		.maxDepth = (float)maxDepth
	};

	vkCmdSetViewport(vkInfo->cmdBuffers[vkInfo->currentFrame], 0, 1, &viewPort);
}

void VulkanSetScissor_impl(Uint32 width, Uint32 height)
{
	//if (!CanVulkanContinueRendering()) return;

	VkRect2D scissor = { 
		.offset.x = 0,
		.offset.y = 0,
		.extent.width = width,
		.extent.height = height,
	};

	vkCmdSetScissor(vkInfo->cmdBuffers[vkInfo->currentFrame], 0, 1, &scissor);
}

void VulkanBindPipeline_impl()
{
	//if (!CanVulkanContinueRendering()) return;

	VulkanGraphicsPipelineBind(vkInfo->cmdBuffers[vkInfo->currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, vkInfo->graphicsPipeline.handle);
}

void VulkanDrawIndex_impl()
{
	//if (!CanVulkanContinueRendering()) return;

	vkCmdDraw(vkInfo->cmdBuffers[vkInfo->currentFrame], 6, 1, 0, 0);
}

void VulkanEndRendering_impl()
{
	//if (!CanVulkanContinueRendering()) return;

	vkInfo->vkCmdEndRenderingKHR(vkInfo->cmdBuffers[vkInfo->currentFrame]);

	for (SizeT i = 0; i < vkInfo->swapChain.images.impl.count; i++)
	{
		vkInfo->imageBarriers[i].sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		vkInfo->imageBarriers[i].pNext = VK_NULL_HANDLE;
		vkInfo->imageBarriers[i].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
		vkInfo->imageBarriers[i].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT;
		vkInfo->imageBarriers[i].oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		vkInfo->imageBarriers[i].newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		vkInfo->imageBarriers[i].srcQueueFamilyIndex = 0;
		vkInfo->imageBarriers[i].dstQueueFamilyIndex = 0;
		vkInfo->imageBarriers[i].image = vkInfo->swapChain.images.data[i];
		vkInfo->imageBarriers[i].subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		vkInfo->imageBarriers[i].subresourceRange.baseMipLevel = 0;
		vkInfo->imageBarriers[i].subresourceRange.levelCount = 1;
		vkInfo->imageBarriers[i].subresourceRange.baseArrayLayer = 0;
		vkInfo->imageBarriers[i].subresourceRange.layerCount = 1;
	}

	vkCmdPipelineBarrier(
		vkInfo->cmdBuffers[vkInfo->currentFrame], VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE,
		(Uint32)vkInfo->swapChain.images.impl.count, vkInfo->imageBarriers
	);
}

Bool VulkanFrameCommandListEnd_impl()
{
	//if (!CanVulkanContinueRendering()) return FALSE;

	return VulkanCommandBufferEnd(vkInfo->cmdBuffers[vkInfo->currentFrame]);
}

Bool VulkanFrameSubmit_impl()
{
	//if (!CanVulkanContinueRendering()) return FALSE;

	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &vkInfo->imageAvailableSemaphores[vkInfo->currentFrame],
		.commandBufferCount = 1,
		.pCommandBuffers = &vkInfo->cmdBuffers[vkInfo->currentFrame],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &vkInfo->queueCompleteSemaphores[vkInfo->currentFrame]
	};

	VkPipelineStageFlags waitStages[1] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	submitInfo.pWaitDstStageMask = waitStages;

	VkResult result = vkQueueSubmit(vkInfo->graphicsQueue, 1, &submitInfo, vkInfo->inFlightFences[vkInfo->currentFrame]);
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to submit vulkan frame : %d", result);
		return FALSE;
	}

	return TRUE;
}

Bool VulkanFramePresent_impl()
{
	VkPresentInfoKHR presentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &vkInfo->queueCompleteSemaphores[vkInfo->currentFrame],
		.swapchainCount = 1,
		.pSwapchains = &vkInfo->swapChain.handle,
		.pImageIndices = &vkInfo->imageIndex,
		.pResults = VK_NULL_HANDLE,
	};

	VkResult result = vkQueuePresentKHR(vkInfo->presentQueue, &presentInfo);

	/*if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		VulkanResizeSwapChain(vkInfo, GetApp()->windowData.w, GetApp()->windowData.h);
	}
	else*/ if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to present vulkan frame : %d", result);
		return FALSE;
	}

	//loop frame index
	vkInfo->currentFrame = (vkInfo->currentFrame + 1) % vkInfo->swapChain.maxFramesInFlight;

	return TRUE;
}

void VulkanWaitIdle_impl()
{
	vkDeviceWaitIdle(vkInfo->logicalDevice);
}

void VulkanShutdown_impl()
{
	VulkanDestroySemaphoresAndFences(vkInfo);
	VulkanDestroyCommandBuffers(vkInfo);
	VulkanDestroyCommandPool(vkInfo);
	VulkanCleanupGraphicsPipeline(vkInfo);

	VulkanDestroyImageView(vkInfo);
	VulkanShutdownImageViewsDefaultData(vkInfo);

	VulkanShutdownSwapChainImages(vkInfo);
	VulkanDestroySwapChain(vkInfo);
	VulkanShutdownSwapChainSupportData(vkInfo);

	VulkanDestroyLogicalDevice(vkInfo);
	VulkanCleanupSurface(vkInfo);

	if (vkInfo->debugger.validationLayer.enableValidationLayers)
	{
		VulkanCleanupDebugMessenger(vkInfo);
	}

	VulkanDestroyInstance(vkInfo);

	if (vkInfo->debugger.validationLayer.enableValidationLayers)
	{
		FE_ListClear(vkInfo->debugger.validationLayer.validationLayers);
	}

	FE_MemoryGeneralFree(vkInfo);
}

void VulkanOnWindowResized_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
	VulkanResizeSwapChain(vkInfo, width, height);

	VulkanFramePrepare_impl();
	VulkanFrameCommandListBegin_impl();
	VulkanBeginRendering_impl(&vkInfo->apiData->defaultClearColor);

	VulkanSetViewport_impl(0, 0, width, height, 0, 1);
	VulkanSetScissor_impl(width, height);
	VulkanBindPipeline_impl();

	VulkanDrawIndex_impl();
	VulkanEndRendering_impl();
	VulkanFrameCommandListEnd_impl();
	VulkanFrameSubmit_impl();
	VulkanFramePresent_impl();
	VulkanWaitIdle_impl();
}

Bool CanVulkanContinueRendering()
{
	return TRUE;
}
