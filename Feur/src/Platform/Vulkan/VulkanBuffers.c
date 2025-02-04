#include "fepch.h"
#include "Platform/Vulkan/VulkanBuffers.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanCommands.h"

void VulkanInitVertexArrayBuffer()
{
	
}

void VulkanCreateBuffer(FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage, FE_VulkanAllocatedBuffer* outAllocatedBuffer)
{
	// allocate buffer
	VkBufferCreateInfo bufferInfo = { 
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = NULL,
		.size = allocSize,
		.usage = usage,
	};

	VmaAllocationCreateInfo vmaAllocInfo = {
		.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE,
		.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT | VMA_ALLOCATION_CREATE_MAPPED_BIT,
		.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
	};

	// allocate the buffer
	VkResult result = vmaCreateBuffer(vkInfo->allocator, &bufferInfo, &vmaAllocInfo, &outAllocatedBuffer->buffer, &outAllocatedBuffer->allocation, &outAllocatedBuffer->info);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to allocate vulkan buffer : %d", result);
}

void VulkanDestroyBuffer(FE_VulkanInfo* vkInfo, FE_VulkanAllocatedBuffer* buffer)
{
	vmaDestroyBuffer(vkInfo->allocator, buffer->buffer, buffer->allocation);
}

FE_VulkanAllocatedBuffer* VulkanCreateVertexBuffer(FE_VulkanInfo* vkInfo, Uint32 vertexCount, SizeT* outVertexBufferId)
{
	FE_VulkanAllocatedBuffer* vertexBuffer = FE_MemoryGeneralAlloc(sizeof(FE_VulkanAllocatedBuffer));
	//VulkanCreateBuffer(vkInfo, vertexCount * sizeof(FE_Vertex3D), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, &vkInfo->vertexBuffer);
	VulkanCreateBuffer(vkInfo, vertexCount * sizeof(FE_Vertex3D), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, vertexBuffer);
	FE_ListPush(vkInfo->vertexBuffers, vertexBuffer->buffer);
	FE_ListPushValue(vkInfo->vertexBuffersOffsets, VkDeviceSize, 0);
	*outVertexBufferId = vkInfo->vertexBuffers.impl.count - 1;

	return vertexBuffer;
}

void VulkanAddVertexIntoBuffer(struct FE_VulkanInfo* vkInfo, FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset, FE_VulkanAllocatedBuffer* allocatedVertexBuffer)
{
	FE_VulkanAllocatedBuffer stagingBuffer;
	VulkanCreateBuffer(vkInfo, vertexCount * sizeof(FE_Vertex3D), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &stagingBuffer);

	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, vertices, stagingBuffer.allocation, verticesOffset, vertexCount * sizeof(FE_Vertex3D));
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	//VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, vkInfo->vertexBuffer.buffer, vertexCount * sizeof(FE_Vertex3D));
	VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, allocatedVertexBuffer->buffer, vertexCount * sizeof(FE_Vertex3D));

	VulkanDestroyBuffer(vkInfo, &stagingBuffer);
}

FE_VulkanAllocatedBuffer* VulkanCreateIndexBuffer(FE_VulkanInfo* vkInfo, Uint32 indexCount, SizeT* outIndexBufferId)
{
	FE_VulkanAllocatedBuffer* indexBuffer = FE_MemoryGeneralAlloc(sizeof(FE_VulkanAllocatedBuffer));
	//VulkanCreateBuffer(vkInfo, indexCount * sizeof(Uint32), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, &vkInfo->indexBuffer);
	VulkanCreateBuffer(vkInfo, indexCount * sizeof(Uint32), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, indexBuffer);
	FE_ListPush(vkInfo->indexBuffers, indexBuffer->buffer);
	*outIndexBufferId = vkInfo->indexBuffers.impl.count - 1;

	return indexBuffer;
}

void VulkanAddIndexIntoBuffer(FE_VulkanInfo* vkInfo, Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset, struct FE_VulkanAllocatedBuffer* allocatedVertexBuffer)
{
	FE_VulkanAllocatedBuffer stagingBuffer;
	VulkanCreateBuffer(vkInfo, indexCount * sizeof(Uint32), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &stagingBuffer);

	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, newIndices, stagingBuffer.allocation, indicesOffset, indexCount * sizeof(Uint32));
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, allocatedVertexBuffer->buffer, indexCount * sizeof(Uint32));

	VulkanDestroyBuffer(vkInfo, &stagingBuffer);
}

void VulkanCreateUniformBuffer(FE_VulkanInfo* vkInfo)
{
	VkDeviceSize bufferSize = sizeof(FE_UniformBufferObject);
	vkInfo->uniformData.uniformBuffers = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * bufferSize);
	vkInfo->uniformData.uniformBuffersMapped = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * bufferSize);

	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++) 
	{
		VulkanCreateBuffer(vkInfo, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &vkInfo->uniformData.uniformBuffers[i]);
		vmaMapMemory(vkInfo->allocator, vkInfo->uniformData.uniformBuffers[i].allocation, &vkInfo->uniformData.uniformBuffersMapped[i]);

		*vkInfo->uniformData.uniformBuffersMapped[i] = (FE_UniformBufferObject){ 
			.ambientLightColor = (FE_Color){1, 1, 1, 0.2f},
			.lightPosition = ILDA_vector3f_one, 
			.lightColor = (FE_Color){1, 1, 1, 1},
		};
	}
}

void VulkanDestroyUniformBuffer(FE_VulkanInfo* vkInfo)
{
	for (SizeT i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		vmaUnmapMemory(vkInfo->allocator, vkInfo->uniformData.uniformBuffers[i].allocation);
		VulkanDestroyBuffer(vkInfo, &vkInfo->uniformData.uniformBuffers[i]);
	}

	FE_MemoryGeneralFree(vkInfo->uniformData.uniformBuffersMapped);
	FE_MemoryGeneralFree(vkInfo->uniformData.uniformBuffers);
}

void VulkanCreateDrawIndexedIndirectCommandsBuffer(FE_VulkanInfo* vkInfo)
{
	VulkanCreateBuffer(vkInfo, sizeof(VkDrawIndexedIndirectCommand), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT, &vkInfo->drawIndexedIndirectCmdBuffer);
}

void VulkanAddDrawIndexedIndirectCommandsBuffer(FE_VulkanInfo* vkInfo, Uint32 indexCount)
{
	//must be same amount of descriptor ans drawIndexedIndirectCmd
	vkInfo->drawIndexedIndirectCmd = (VkDrawIndexedIndirectCommand){
		.instanceCount = 1,
		.firstInstance = 0,
		.firstIndex = 0,
		.indexCount = indexCount,
		.vertexOffset = 0,
	};

	FE_VulkanAllocatedBuffer stagingBuffer;
	VulkanCreateBuffer(vkInfo, sizeof(VkDrawIndexedIndirectCommand), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &stagingBuffer);

	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, &vkInfo->drawIndexedIndirectCmd, stagingBuffer.allocation, 0, sizeof(VkDrawIndexedIndirectCommand));
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, vkInfo->drawIndexedIndirectCmdBuffer.buffer, sizeof(VkDrawIndexedIndirectCommand));

	VulkanDestroyBuffer(vkInfo, &stagingBuffer);
}

void VulkanUpdateUniformBuffer(FE_VulkanInfo* vkInfo, const FE_Camera3D* cam)
{
	FE_UniformBufferObject ubo = {
		.mvp = cam->mvp,
		.ambientLightColor = vkInfo->uniformData.uniformBuffersMapped[vkInfo->currentFrame]->ambientLightColor,
		.lightColor = vkInfo->uniformData.uniformBuffersMapped[vkInfo->currentFrame]->lightColor,
		.lightPosition = vkInfo->uniformData.uniformBuffersMapped[vkInfo->currentFrame]->lightPosition,
	};

	memcpy(vkInfo->uniformData.uniformBuffersMapped[vkInfo->currentFrame], &ubo, sizeof(ubo));
}

void VulkanBindBuffers(FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer, SizeT indexBufferId, SizeT vertexBufferId)
{
	//vkCmdBindVertexBuffers(cmdBuffer, 0, (Uint32)vkInfo->vertexBuffers.impl.count, vkInfo->vertexBuffers.data, vkInfo->vertexBuffersOffsets.data);
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &vkInfo->vertexBuffers.data[indexBufferId], vkInfo->vertexBuffersOffsets.data);

	vkCmdBindIndexBuffer(vkInfo->cmdBuffers[vkInfo->currentFrame], vkInfo->indexBuffers.data[indexBufferId], 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkInfo->graphicsPipeline.layout, 0, 1, &vkInfo->descriptor.sets[vkInfo->currentFrame], 0, NULL);
}

void VulkanCopyBuffer(FE_VulkanInfo* vkInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
	VkCommandBufferAllocateInfo allocInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandPool = vkInfo->graphicsCommandPool,
		.commandBufferCount = 1,
	};

	VkCommandBuffer commandBuffer;
	VulkanCommandBufferAllocAndBeginSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &commandBuffer);

	VkBufferCopy copyRegion = {
		.size = size
	};
	
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	VulkanCommandBufferEndAndFreeSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &commandBuffer, vkInfo->graphicsQueue);
}
