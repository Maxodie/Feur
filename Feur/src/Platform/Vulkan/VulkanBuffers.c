#include "fepch.h"
#include "Platform/Vulkan/VulkanBuffers.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanCommands.h"

void VulkanInitVertexArrayBuffer()
{
	
}

FE_VulkanAllocatedBuffer VulkanCreateBuffer(FE_VulkanInfo* vkInfo, SizeT allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage)
{
	// allocate buffer
	VkBufferCreateInfo bufferInfo = { 
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = NULL,
		.size = allocSize,
		.usage = usage,
	};

	VmaAllocationCreateInfo vmaallocInfo = {
		.usage = memoryUsage,
		.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT,
	};

	FE_VulkanAllocatedBuffer newBuffer = { 0 };

	// allocate the buffer
	VkResult result = vmaCreateBuffer(vkInfo->allocator, &bufferInfo, &vmaallocInfo, &newBuffer.buffer, &newBuffer.allocation, &newBuffer.info);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to allocate vulkan buffer : %d", result);

	return newBuffer;
}

void VulkanDestroyBuffer(FE_VulkanInfo* vkInfo, const FE_VulkanAllocatedBuffer* buffer)
{
	vmaDestroyBuffer(vkInfo->allocator, buffer->buffer, buffer->allocation);
}

FE_VulkanGPUMeshBuffers VulkanUploadMeshBuffer(FE_VulkanInfo* vkInfo, const FE_Mesh* mesh)
{
	const SizeT vertexBufferSize = mesh->vertices.impl.count * sizeof(FE_Vertex3D);
	const SizeT indexBufferSize = mesh->indices.impl.count * sizeof(Uint32);

	FE_VulkanGPUMeshBuffers gpuMeshBuffer = { 0 };

	//create vertex buffer
	gpuMeshBuffer.vertexBuffer = VulkanCreateBuffer(
		vkInfo, vertexBufferSize, 
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT, VMA_MEMORY_USAGE_GPU_ONLY
	);

	//find the adress of the vertex buffer
	VkBufferDeviceAddressInfo deviceAdressInfo = { 
		.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
		.buffer = gpuMeshBuffer.vertexBuffer.buffer 
	};

	gpuMeshBuffer.vertexBufferAddress = vkGetBufferDeviceAddress(vkInfo->logicalDevice, &deviceAdressInfo);

	//create index buffer
	gpuMeshBuffer.indexBuffer = VulkanCreateBuffer(
		vkInfo, indexBufferSize, 
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VMA_MEMORY_USAGE_GPU_ONLY
	);

	FE_VulkanAllocatedBuffer staging = VulkanCreateBuffer(
		vkInfo, vertexBufferSize + indexBufferSize, 
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY
	);

	// copy vertex buffer
	VkResult result = vmaCopyMemoryToAllocation(vkInfo->allocator, mesh->vertices.data, staging.allocation, 0, vertexBufferSize);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);
	// copy index buffer
	result = vmaCopyMemoryToAllocation(vkInfo->allocator, mesh->indices.data, staging.allocation, vertexBufferSize, indexBufferSize);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to copy memory into vulkan allocator : %d", result);

	VkCommandBuffer cmdBuffer;
	VulkanCommandBufferAllocAndBeginSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &cmdBuffer);

	VkBufferCopy vertexCopy = {
	vertexCopy.dstOffset = 0,
	vertexCopy.srcOffset = 0,
	vertexCopy.size = mesh->vertices.impl.count,
	};

	vkCmdCopyBuffer(cmdBuffer, staging.buffer, gpuMeshBuffer.vertexBuffer.buffer, 1, &vertexCopy);

	VkBufferCopy indexCopy = {
		.dstOffset = 0,
		.srcOffset = vertexBufferSize,
		.size = indexBufferSize,
	};

	vkCmdCopyBuffer(cmdBuffer, staging.buffer, gpuMeshBuffer.indexBuffer.buffer, 1, &indexCopy);

	VulkanCommandBufferEndAndFreeSingleUse(vkInfo->logicalDevice, vkInfo->graphicsCommandPool, &cmdBuffer, vkInfo->graphicsQueue);

	VulkanDestroyBuffer(vkInfo, &staging);

	return gpuMeshBuffer;
}
