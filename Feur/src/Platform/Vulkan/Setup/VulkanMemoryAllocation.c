#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanMemoryAllocation.h"

#include "Platform/Vulkan/Setup/VulkanSetup.h"

void VulkanCreateAllocator(FE_VulkanInfo* vkInfo)
{
    VmaAllocatorCreateInfo allocatorInfo = {
        .physicalDevice = vkInfo->physicalDevice.GPU,
        .device = vkInfo->logicalDevice,
        .instance = vkInfo->instance,
        .flags = VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT,
    };

    vmaCreateAllocator(&allocatorInfo, &vkInfo->allocator);
}

void VulkanDestroyAllocator(FE_VulkanInfo* vkInfo)
{
    vmaDestroyAllocator(vkInfo->allocator);
}
