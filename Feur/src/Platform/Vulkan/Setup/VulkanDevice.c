#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

Bool FE_API VulkanIsQueueFamilyIndicesCompleted(VulkanfeQueueFamilyIndices* vkQueueFamilyIndices)
{
	return vkQueueFamilyIndices->graphicsFamily.hasValue;
}

void FE_API VulkanPickPhysicalDevice(VulkanfeInfo* vkInfo)
{
	vkInfo->physicalDevice = VK_NULL_HANDLE;

	//List aall physical devices
	Uint32 deviceCount = 0;
	vkEnumeratePhysicalDevices(vkInfo->vkInstance, &deviceCount, NULL);

	if (deviceCount == 0) 
	{
		FE_CORE_ASSERT(FALSE, "Failed to find GPUs with Vulkan support!");
	}

	VkPhysicalDevice* devices = FE_MemoryGeneralAlloc(deviceCount * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(vkInfo->vkInstance, &deviceCount, devices);

	for (Uint32 i = 0; i < deviceCount; i++)
	{
		if (VulkanPhysicalDeviceSuitable(devices[i])) {
			vkInfo->physicalDevice = devices[i];
			break;
		}
	}

#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan GPU available ==");
	VkPhysicalDeviceProperties deviceProperties;
	for (Uint32 i = 0; i < deviceCount; i++)
	{
		vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
		FE_CORE_LOG_SUCCESS("   - NAME   %s", deviceProperties.deviceName);
	}
#endif // !FE_DIST

	FE_MemoryGeneralFree(devices);

	if (vkInfo->physicalDevice == VK_NULL_HANDLE) {
		FE_CORE_ASSERT(FALSE, "Failed to find a suitable GPU!");
	}

#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan Chosen GPU ==");
	vkGetPhysicalDeviceProperties(vkInfo->physicalDevice, &deviceProperties);
	FE_CORE_LOG_SUCCESS("   - NAME   %s", deviceProperties.deviceName);
#endif // !FE_DIST
}

Bool FE_API VulkanPhysicalDeviceSuitable(VkPhysicalDevice device)
{
	VulkanfeQueueFamilyIndices indices = VulkanFindQueueFamilies(device);
	return VulkanIsQueueFamilyIndicesCompleted(&indices);
}

VulkanfeQueueFamilyIndices FE_API VulkanFindQueueFamilies(VkPhysicalDevice device)
{
	VulkanfeQueueFamilyIndices indices = { 0 };

	Uint32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

	VkQueueFamilyProperties* queueFamilies = FE_MemoryGeneralAlloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

	for (Uint32 y = 0; y < queueFamilyCount; y++) 
	{
		if (queueFamilies[y].queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			FE_OptionalSetValue(indices.graphicsFamily, y);
			Bool value = indices.graphicsFamily.hasValue;
		}

		if (VulkanIsQueueFamilyIndicesCompleted(&indices))
		{
			break;
		}
	}

	FE_MemoryGeneralFree(queueFamilies);

	return indices;
}

void FE_API VulkanCreateLogicalDevice(VulkanfeInfo* vkInfo)
{
	VulkanfeQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo->physicalDevice);
	
	//Queues
	Float32 queuePriority = 1.0f;

	VkDeviceQueueCreateInfo queueCreateInfo = { 
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.queueFamilyIndex = indices.graphicsFamily.value,
		.queueCount = 1,
		.pQueuePriorities = &queuePriority
	};
	//features
	VkPhysicalDeviceFeatures deviceFeatures = { 0 };
	VkDeviceCreateInfo createInfo = {
	.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
	.pQueueCreateInfos = &queueCreateInfo,
	.queueCreateInfoCount = 1,
	.pEnabledFeatures = &deviceFeatures,
	.enabledExtensionCount = 0
	};

	if (vkInfo->enableValidationLayers) 
	{
		createInfo.enabledLayerCount = (Uint32)vkInfo->validationLayers.impl.count;
		//createInfo.ppEnabledLayerNames = vkInfo->validationLayers.data;
	}
	else 
	{
		createInfo.enabledLayerCount = 0;
	}

	//create device based on pyshical device and createInfo
	if (vkCreateDevice(vkInfo->physicalDevice, &createInfo, NULL, &vkInfo->device) != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to create logical device!");
	}

	//store graphic queue into vkInfo->graphicsQueue
	vkGetDeviceQueue(vkInfo->device, indices.graphicsFamily.value, 0, &vkInfo->graphicsQueue);
}
