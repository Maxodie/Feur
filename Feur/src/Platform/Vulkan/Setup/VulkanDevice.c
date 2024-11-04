#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

Bool FE_API VulkanIsQueueFamilyIndicesCompleted(VulkanfeQueueFamilyIndices* vkQueueFamilyIndices)
{
	return vkQueueFamilyIndices->graphicsFamily.hasValue && vkQueueFamilyIndices->presentFamily.hasValue;
}

void FE_API VulkanPickPhysicalDevice(VulkanfeInfo* vkInfo)
{
	vkInfo->physicalDevice = VK_NULL_HANDLE;

	//List aall physical devices
	Uint32 deviceCount = 0;
	vkEnumeratePhysicalDevices(vkInfo->vkInstance, &deviceCount, NULL);

	FE_CORE_ASSERT(deviceCount > 0, "Failed to find GPUs with Vulkan support!");

	VkPhysicalDevice* devices = FE_MemoryGeneralAlloc(deviceCount * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(vkInfo->vkInstance, &deviceCount, devices);

	for (Uint32 i = 0; i < deviceCount; i++)
	{
		if (VulkanPhysicalDeviceSuitable(vkInfo, devices[i])) {
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

	FE_CORE_ASSERT(vkInfo->physicalDevice != VK_NULL_HANDLE, "Failed to find a suitable GPU!");

#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan Chosen GPU ==");
	vkGetPhysicalDeviceProperties(vkInfo->physicalDevice, &deviceProperties);
	FE_CORE_LOG_SUCCESS("   - NAME   %s", deviceProperties.deviceName);
#endif // !FE_DIST
}

Bool FE_API VulkanPhysicalDeviceSuitable(const VulkanfeInfo* vkInfo, VkPhysicalDevice device)
{
	VulkanfeQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo, device);
	return VulkanIsQueueFamilyIndicesCompleted(&indices);
}

VulkanfeQueueFamilyIndices FE_API VulkanFindQueueFamilies(const VulkanfeInfo* vkInfo, VkPhysicalDevice device)
{
	VulkanfeQueueFamilyIndices indices = { 0 };

	Uint32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

	VkQueueFamilyProperties* queueFamilies = FE_MemoryGeneralAlloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

	VkBool32 presentSupport = VK_FALSE;
	for (Uint32 i = 0; i < queueFamilyCount; i++) 
	{
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			FE_OptionalSetValue(indices.graphicsFamily, i);
		}
		
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vkInfo->surface, &presentSupport);

		if (presentSupport) {
			FE_OptionalSetValue(indices.presentFamily, i);
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
	VulkanfeQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo, vkInfo->physicalDevice);
	
	FE_List(VkDeviceQueueCreateInfo) queueCreateInfos = { 0 };
	FE_ListInit(queueCreateInfos);

	FE_List(Uint32) uniqueQueueFamilies = { 0 };
	FE_ListInit(uniqueQueueFamilies);
	FE_ListPush(uniqueQueueFamilies, indices.graphicsFamily.value);
	FE_ListPush(uniqueQueueFamilies, indices.presentFamily.value);

	FE_ListRemoveDuplicate(uniqueQueueFamilies);

	if (uniqueQueueFamilies.impl.count > 1)
	{
		qsort(uniqueQueueFamilies.data, uniqueQueueFamilies.impl.count, sizeof(Uint32), Fe_SortInt32Ascending);
	}


	//Queues
	Float32 queuePriority = 1.0f;

	for (Uint32 i = 0; i < uniqueQueueFamilies.impl.count; i++)
	{
		VkDeviceQueueCreateInfo queueCreateInfo = { 
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = uniqueQueueFamilies.data[i],
			.queueCount = 1,
			.pQueuePriorities = &queuePriority
		};
		FE_ListPush(queueCreateInfos, queueCreateInfo);
	}

	//features
	VkPhysicalDeviceFeatures deviceFeatures = { 0 };
	VkDeviceCreateInfo createInfo = {
	.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
	.queueCreateInfoCount = (Uint32)queueCreateInfos.impl.count,
	.pQueueCreateInfos = queueCreateInfos.data,
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
	VkResult success = vkCreateDevice(vkInfo->physicalDevice, &createInfo, NULL, &vkInfo->device);
	FE_CORE_ASSERT(success == VK_SUCCESS, "failed to create logical device!");

	//store queues into vkInfo->*Queue
	vkGetDeviceQueue(vkInfo->device, indices.graphicsFamily.value, 0, &vkInfo->graphicsQueue);
	vkGetDeviceQueue(vkInfo->device, indices.presentFamily.value, 0, &vkInfo->presentQueue);
}
