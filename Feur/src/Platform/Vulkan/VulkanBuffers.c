#include "fepch.h"
#include "Platform/Vulkan/VulkanBuffers.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanCommands.h"

void VulkanInitVertexArrayBuffer()
{
	
}

FE_VulkanAllocatedBuffer VulkanCreateBuffer(FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage)
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

	FE_VulkanAllocatedBuffer newBuffer = { 0 };

	// allocate the buffer
	VkResult result = vmaCreateBuffer(vkInfo->allocator, &bufferInfo, &vmaAllocInfo, &newBuffer.buffer, &newBuffer.allocation, &newBuffer.info);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to allocate vulkan buffer : %d", result);

	return newBuffer;
}

void VulkanDestroyBuffer(FE_VulkanInfo* vkInfo, const FE_VulkanAllocatedBuffer* buffer)
{
	vmaDestroyBuffer(vkInfo->allocator, buffer->buffer, buffer->allocation);
}

void VulkanBindMeshBuffer(FE_VulkanInfo* vkInfo, VkCommandBuffer cmdBuffer, FE_VulkanAllocatedBuffer* verticesBuffer, FE_VulkanAllocatedBuffer* indicesBuffer, const FE_Mesh* mesh)
{
	const SizeT vertexBufferSize = mesh->vertices.impl.count * sizeof(FE_Vertex3D);
	const SizeT indexBufferSize = mesh->indices.impl.count * sizeof(Uint32);

	//FE_VulkanGPUMeshBuffers gpuMeshBuffer = { 0 };

	////create vertex buffer
	//gpuMeshBuffer.vertexBuffer = VulkanCreateBuffer(
	//	vkInfo, vertexBufferSize,
	//	VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, VMA_MEMORY_USAGE_GPU_ONLY
	//);

	////find the adress of the vertex buffer
	//VkBufferDeviceAddressInfo deviceAdressInfo = { 
	//	.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
	//	.buffer = gpuMeshBuffer.vertexBuffer.buffer 
	//};

	//gpuMeshBuffer.vertexBufferAddress = vkGetBufferDeviceAddress(vkInfo->logicalDevice, &deviceAdressInfo);

	////create index buffer
	//gpuMeshBuffer.indexBuffer = VulkanCreateBuffer(
	//	vkInfo, indexBufferSize,
	//	VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VMA_MEMORY_USAGE_GPU_ONLY
	//);

	

	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 1, &verticesBuffer->buffer, offsets);
	vkCmdBindIndexBuffer(cmdBuffer, indicesBuffer->buffer, 0, VK_INDEX_TYPE_UINT32);

	//VkCommandBuffer cmdBuffer;
	//VulkanCommandBufferAllocAndBeginSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &cmdBuffer);

	//VkBufferCopy vertexCopy = {
	//vertexCopy.dstOffset = 0,
	//vertexCopy.srcOffset = 0,
	//vertexCopy.size = mesh->vertices.impl.count,
	//};

	//vkCmdCopyBuffer(cmdBuffer, staging.buffer, gpuMeshBuffer.vertexBuffer.buffer, 1, &vertexCopy);

	/*VkBufferCopy indexCopy = {
		.dstOffset = 0,
		.srcOffset = vertexBufferSize,
		.size = indexBufferSize,
	};*/

	//vkCmdCopyBuffer(cmdBuffer, staging.buffer, gpuMeshBuffer.indexBuffer.buffer, 1, &indexCopy);

	//VulkanCommandBufferEndAndFreeSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &cmdBuffer, vkInfo->graphicsQueue);

	

	//return gpuMeshBuffer;
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
