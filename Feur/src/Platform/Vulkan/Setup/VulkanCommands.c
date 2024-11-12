#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanCommands.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

Bool VulkanCommandBufferAlloc(VkDevice logicalDevice, VkCommandPool cmdPool, Bool isPrimary, VkCommandBuffer* outCmdBuffer)
{
	VkCommandBufferAllocateInfo allocInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = cmdPool,
		.level = isPrimary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY,
		.commandBufferCount = 1,
		.pNext = VK_NULL_HANDLE,
	};

	VkResult result = vkAllocateCommandBuffers(logicalDevice, &allocInfo, outCmdBuffer);
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to allocate command buffer : %d", result);
		return FALSE;
	}

	return TRUE;
}

void VulkanCommandBufferFree(VkDevice logicalDevice, VkCommandPool cmdPool, VkCommandBuffer* cmdBuffer)
{
	vkFreeCommandBuffers(logicalDevice, cmdPool, 1, cmdBuffer);
	cmdBuffer = NULL;
}

Bool VulkanCommandBufferBegin(VkCommandBuffer cmdBuffer, Bool isSingleUse)
{
	VkCommandBufferBeginInfo beginInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = 0,
		.pNext = VK_NULL_HANDLE,
		.pInheritanceInfo = VK_NULL_HANDLE,
	};

	if (isSingleUse)
	{
		beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	}

	VkResult result = vkBeginCommandBuffer(cmdBuffer, &beginInfo);
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to begin command buffer : %d", result);
		return FALSE;
	}

	return TRUE;
}

Bool VulkanCommandBufferEnd(VkCommandBuffer cmdBuffer)
{
	VkResult result = vkEndCommandBuffer(cmdBuffer);
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to end command buffer : %d", result);
		return FALSE;
	}

	return TRUE;
}

Bool VulkanCommandBufferReset(VkCommandBuffer cmdBuffer)
{
	VkResult result = vkResetCommandBuffer(cmdBuffer, 0);
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to reset command buffer : %d", result);
		return FALSE;
	}

	return TRUE;
}

void VulkanCommandBufferAllocAndBeginSingleUse(VkDevice logicalDevice, VkCommandPool pool, VkCommandBuffer* outCmdBuffer)
{
	VulkanCommandBufferAlloc(logicalDevice, pool, TRUE, outCmdBuffer);
	VulkanCommandBufferBegin(*outCmdBuffer, TRUE);
}

void VulkanCommandBufferEndAndFreeSingleUse(VkDevice logicalDevice, VkCommandPool pool, VkCommandBuffer* cmdBuffer, VkQueue graphicsQueue)
{
	VulkanCommandBufferEnd(*cmdBuffer);

	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.commandBufferCount = 1,
		.pCommandBuffers = cmdBuffer,
	};

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, NULL);

	//wait for it to finish
	vkQueueWaitIdle(graphicsQueue);

	//free cmd buffer
	VulkanCommandBufferFree(logicalDevice, pool,  cmdBuffer);
}

void VulkanCreateCommandPool(FE_VulkanInfo* vkInfo)
{
	VkCommandPoolCreateInfo cmdPoolCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = vkInfo->queueFamilyIndices.graphicsFamily.value,
	};

	VkResult result = vkCreateCommandPool(vkInfo->logicalDevice, &cmdPoolCreateInfo, NULL, &vkInfo->graphicsCommandPool);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create graphics command pool : %d", result);

	FE_CORE_LOG_SUCCESS("Vulkand graphics command pool successfuly created");
}

void VulkanDestroyCommandPool(FE_VulkanInfo* vkInfo)
{
	vkDestroyCommandPool(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, NULL);
}

void VulkanCreateCommandBuffers(FE_VulkanInfo* vkInfo)
{
	vkInfo->cmdBuffers = FE_MemoryGeneralAlloc(sizeof(VkCommandBuffer) * vkInfo->swapChain.maxFramesInFlight);

	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		VulkanCommandBufferAlloc(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, TRUE, &vkInfo->cmdBuffers[i]);
	}

	FE_CORE_LOG_SUCCESS("Vulkand graphics command buffers successfuly created");
}

void VulkanDestroyCommandBuffers(FE_VulkanInfo* vkInfo)
{
	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		VulkanCommandBufferFree(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &vkInfo->cmdBuffers[i]);
	}

	FE_MemoryGeneralFree(vkInfo->cmdBuffers);
}