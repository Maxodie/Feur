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
		.requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
	};

	// allocate the buffer
	VkResult result = vmaCreateBuffer(vkInfo->allocator, &bufferInfo, &vmaAllocInfo, &outAllocatedBuffer->buffer, &outAllocatedBuffer->allocation, &outAllocatedBuffer->info);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to allocate vulkan buffer : %d", result);
}

void VulkanDestroyBuffer(FE_VulkanInfo* vkInfo, const FE_VulkanAllocatedBuffer* buffer)
{
	vmaDestroyBuffer(vkInfo->allocator, buffer->buffer, buffer->allocation);
}

void VulkanCreateVertexBuffer(FE_VulkanInfo* vkInfo, Uint32 vertexCount)
{
	VulkanCreateBuffer(vkInfo, vertexCount * sizeof(FE_Vertex3D), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, &vkInfo->vertexBuffer);
}

void VulkanAddVertexIntoBuffer(struct FE_VulkanInfo* vkInfo, FE_Vertex3D* vertices, Uint32 vertexCount, Uint64 verticesOffset)
{
	FE_VulkanAllocatedBuffer stagingBuffer;
	VulkanCreateBuffer(vkInfo, vertexCount * sizeof(FE_Vertex3D), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &stagingBuffer);

	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, vertices, stagingBuffer.allocation, verticesOffset, vertexCount * sizeof(FE_Vertex3D));
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, vkInfo->vertexBuffer.buffer, vertexCount * sizeof(FE_Vertex3D));

	VulkanDestroyBuffer(vkInfo, &stagingBuffer);
}

void VulkanCreateIndexBuffer(FE_VulkanInfo* vkInfo, Uint32 indexCount)
{
	VulkanCreateBuffer(vkInfo, indexCount * sizeof(Uint32), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, &vkInfo->indexBuffer);
}

void VulkanAddIndexIntoBuffer(FE_VulkanInfo* vkInfo, Uint32* newIndices, Uint32 indexCount, Uint64 indicesOffset)
{
	FE_VulkanAllocatedBuffer stagingBuffer;
	VulkanCreateBuffer(vkInfo, indexCount * sizeof(Uint32), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, &stagingBuffer);

	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, newIndices, stagingBuffer.allocation, indicesOffset, indexCount * sizeof(Uint32));
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	VulkanCopyBuffer(vkInfo, stagingBuffer.buffer, vkInfo->indexBuffer.buffer, indexCount * sizeof(Uint32));

	VulkanDestroyBuffer(vkInfo, &stagingBuffer);
}

void VulkanCreateUniformBuffer(FE_VulkanInfo* vkInfo)
{
	VkDeviceSize bufferSize = sizeof(FE_UniformBufferObject);
	vkInfo->uniformData.uniformBuffers = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * bufferSize);
	vkInfo->uniformData.uniformBuffersMapped = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * bufferSize);

	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++) {
		VulkanCreateBuffer(vkInfo, bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &vkInfo->uniformData.uniformBuffers[i]);

		vmaMapMemory(vkInfo->allocator, vkInfo->uniformData.uniformBuffers[i].allocation, &vkInfo->uniformData.uniformBuffersMapped[i]);
	}
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

void VulkanUpdateUniformBuffer(FE_VulkanInfo* vkInfo)
{
	ILDA_vector3f axis = { .x = 0, .y = 0.0, .z = 0.0 };
	ILDA_matrix4x4 rotation = ILDA_rotation(ILDA_radians(0.f), &axis);


	ILDA_vector3f pos = { .x = -0.0f, .y =0, .z = -2.0f }, target = { 0 }, worldUp = { .y = 1.0f };
	ILDA_matrix4x4 view = ILDA_matrix_look_at_r(&pos, &target, &worldUp);

	ILDA_matrix4x4 perspective = ILDA_matrix_perspective_r(ILDA_radians(45), vkInfo->swapChain.extent.width / (float)vkInfo->swapChain.extent.height, 0.1f, 10.0f);

	rotation.data[3][3] = 1;
	perspective.data[1][1] *= -1;
	FE_UniformBufferObject ubo = {
		.model = rotation,
		.view = view,
		.proj = perspective,
	};

	memcpy(vkInfo->uniformData.uniformBuffersMapped[vkInfo->currentFrame], &ubo, sizeof(ubo));
}

void VulkanBindBuffers(FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer)
{
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &vkInfo->vertexBuffer.buffer, offsets);
	vkCmdBindIndexBuffer(cmdBuffer, vkInfo->indexBuffer.buffer, 0, VK_INDEX_TYPE_UINT32);
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
