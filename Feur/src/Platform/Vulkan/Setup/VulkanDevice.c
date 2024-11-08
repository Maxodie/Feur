#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"

Bool FE_API VulkanIsQueueFamilyIndicesCompleted(FE_VulkanQueueFamilyIndices* vkQueueFamilyIndices)
{
	return vkQueueFamilyIndices->graphicsFamily.hasValue && vkQueueFamilyIndices->presentFamily.hasValue;
}

void FE_API VulkanInitDefaultDeviceSelection(FE_VulkanInfo* vkInfo)
{
	vkInfo->physicalDevice.GPU = VK_NULL_HANDLE;
}

void FE_API VulkanPickPhysicalDevice(FE_VulkanInfo* vkInfo)
{
	FE_VulkanPysicalDevice* fePhysicalDevice = &vkInfo->physicalDevice;

	//List aall physical devices
	Uint32 deviceCount = 0;
	vkEnumeratePhysicalDevices(vkInfo->instance, &deviceCount, NULL);

	FE_CORE_ASSERT(deviceCount > 0, "Failed to find GPUs with Vulkan support!");

	VkPhysicalDevice* devices = FE_MemoryGeneralAlloc(deviceCount * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(vkInfo->instance, &deviceCount, devices);

	/*------------------ Search for physical device ------------------*/
	for (Uint32 i = 0; i < deviceCount; i++)
	{
		if (VulkanSelectPhysicalDevice(vkInfo, devices[i])) {
			break;
		}
	}

	/*------------------ Show Total Search Results ------------------*/
#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan GPU available ==");
	for (Uint32 i = 0; i < deviceCount; i++)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(devices[i], &properties);
		FE_CORE_LOG_SUCCESS("   - NAME   %s", properties.deviceName);
	}
#endif

	/*------------------ Cleanup And Check Selected Result ------------------*/
	FE_MemoryGeneralFree(devices);

	FE_CORE_ASSERT(fePhysicalDevice->GPU != VK_NULL_HANDLE, "Failed to find a suitable GPU!");

	/*------------------ Show Selected Results ------------------*/
#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan Chosen GPU ==");
	FE_CORE_LOG_SUCCESS("   - NAME   %s", fePhysicalDevice->properties.deviceName);
#endif // !FE_DIST

	FE_CORE_LOG_SUCCESS("Vulkan physical device selected");
}

Bool FE_API VulkanSelectPhysicalDevice(FE_VulkanInfo* vkInfo, VkPhysicalDevice device)
{
	/*--------------------- Check For Physical Device Support ---------------------*/
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	VkPhysicalDeviceMemoryProperties deviceMemoryProperties;
	vkGetPhysicalDeviceMemoryProperties(device, &deviceMemoryProperties);

	//base reuirement
	if (!deviceFeatures.samplerAnisotropy)
	{
		FE_CORE_LOG_DEBUG("GPU [%s] does not support sampler anisotropy, skipping...", deviceProperties.deviceName);
		return FALSE;
	}

	Bool supportsDeviceLocalHostVisible = FALSE;
	// check if device support local/host visible
	for (Uint32 i = 0; i < deviceMemoryProperties.memoryTypeCount; i++)
	{
		if ((deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0 &&
			(deviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0)
		{
			supportsDeviceLocalHostVisible = TRUE;
			break;
		}
	}

	if (supportsDeviceLocalHostVisible)
	{
		FE_CORE_LOG_DEBUG("GPU [%s] support Local Host Visible", deviceProperties.deviceName);
	}

	/*--------------------- Cache Current GPU ---------------------*/
	vkInfo->physicalDevice.GPU = device;
	vkInfo->physicalDevice.properties = deviceProperties;
	vkInfo->physicalDevice.features = deviceFeatures;
	vkInfo->physicalDevice.memoryProperties = deviceMemoryProperties;
	vkInfo->physicalDevice.supportDeviceLocalHostVisible = supportsDeviceLocalHostVisible;


	/*--------------------- Check For Queues Family ---------------------*/
	FE_VulkanQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo, device);
	//Bool extensionsSupported = VulkanSelectLogicalDevice(vkInfo, device);

	Bool swapChainAdequate = FALSE;
	VulkanfeSwapChainSupportDetails swapChainSupport = VulkanQuerySwapChainSupport(vkInfo, device);
	swapChainAdequate = !(swapChainSupport.formats.impl.count == 0) && !(swapChainSupport.presentModes.impl.count == 0);

	VulkanClearSwapChainSupport(&swapChainSupport);
	return VulkanIsQueueFamilyIndicesCompleted(&indices) && /*extensionsSupported && */ swapChainAdequate;
}

FE_VulkanQueueFamilyIndices FE_API VulkanFindQueueFamilies(const FE_VulkanInfo* vkInfo, VkPhysicalDevice device)
{
	FE_VulkanQueueFamilyIndices indices = { 0 };

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

void FE_API VulkanCreateLogicalDevice(FE_VulkanInfo* vkInfo)
{
	FE_VulkanPysicalDevice* physicalDevice = &vkInfo->physicalDevice;
	/*--------------------- Check For Device Extension Support ---------------------*/
	Bool portabilityExtensionRequired = FALSE;

	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(physicalDevice->GPU, NULL, &extensionCount, NULL);

	if (extensionCount > 0)
	{
		VkExtensionProperties* availableExtensions = FE_MemoryGeneralAlloc(extensionCount * sizeof(VkExtensionProperties));
		vkEnumerateDeviceExtensionProperties(physicalDevice->GPU, NULL, &extensionCount, availableExtensions);

		for (Uint32 i = 0; i < extensionCount; i++)
		{
			if (strcmp(availableExtensions[i].extensionName, "VK_KHR_portability_subset") == 0)
			{
				FE_CORE_LOG_DEBUG("Adding required device extension 'VK_KHR_portability_subset'");
				portabilityExtensionRequired = TRUE;
			}
		}

		FE_MemoryGeneralFree(availableExtensions);
	}

	FE_List(const char*) requiredDeviceExtensionsNames = { 0 };
	FE_ListInit(requiredDeviceExtensionsNames);
	FE_ListReserve(requiredDeviceExtensionsNames, 6);
	FE_ListPushValue(requiredDeviceExtensionsNames, const char*, "VK_KHR_swapchain");

	if (portabilityExtensionRequired)
	{
		FE_ListPushValue(requiredDeviceExtensionsNames, const char*, "VK_KHR_portability_subset");
	}

	VkPhysicalDeviceFeatures2 deviceFeature = {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR,
		.features.samplerAnisotropy = physicalDevice->features.samplerAnisotropy,
		.features.fillModeNonSolid = physicalDevice->features.fillModeNonSolid,
		.features.shaderClipDistance = physicalDevice->features.shaderClipDistance,
	};

	if (!deviceFeature.features.shaderClipDistance)
	{
		FE_CORE_LOG_ERROR("ShaderClipDistance not supported by vulkan device '%s'", physicalDevice->properties.deviceName);
	}

	VkPhysicalDeviceDynamicRenderingFeatures dynamicrendering = {
		.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES,
		.dynamicRendering = VK_TRUE,
		.pNext = &dynamicrendering
	};
	FE_ListPushValue(requiredDeviceExtensionsNames, const char*, VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);

	/*--------------------- Find Queue Families ---------------------*/
	FE_VulkanQueueFamilyIndices indices = VulkanFindQueueFamilies(vkInfo, vkInfo->physicalDevice.GPU);
	
	FE_List(VkDeviceQueueCreateInfo) queueCreateInfos = { 0 };
	FE_ListInit(queueCreateInfos);

	FE_List(Uint32) uniqueQueueFamilies = { 0 };
	FE_ListInit(uniqueQueueFamilies);
	FE_ListReserve(uniqueQueueFamilies, 2);
	FE_ListPush(uniqueQueueFamilies, indices.graphicsFamily.value);
	FE_ListPush(uniqueQueueFamilies, indices.presentFamily.value);

	FE_ListRemoveDuplicate(uniqueQueueFamilies);

	if (uniqueQueueFamilies.impl.count > 1)
	{
		qsort(uniqueQueueFamilies.data, uniqueQueueFamilies.impl.count, sizeof(Uint32), Fe_SortInt32Ascending);
	}

	Float32 queuePriority = 1.0f;

	FE_ListReserve(queueCreateInfos, uniqueQueueFamilies.impl.count);

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

	/*--------------------- Fill Create infos ---------------------*/
	VkDeviceCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.enabledExtensionCount = (Uint32)requiredDeviceExtensionsNames.impl.count,
		.ppEnabledExtensionNames = requiredDeviceExtensionsNames.data,
		.queueCreateInfoCount = (Uint32)queueCreateInfos.impl.count,
		.pQueueCreateInfos = queueCreateInfos.data,
		.pNext = &deviceFeature,
	};

	if (vkInfo->validationLayer.enableValidationLayers)
	{
		createInfo.enabledLayerCount = (Uint32)vkInfo->validationLayer.validationLayers.impl.count;
		createInfo.ppEnabledLayerNames = vkInfo->validationLayer.validationLayers.data;
	}
	else 
	{
		createInfo.enabledLayerCount = 0;
	}

	//create device based on pyshical device and createInfo
	VkResult result = vkCreateDevice(vkInfo->physicalDevice.GPU, &createInfo, NULL, &vkInfo->device);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create logical device! - %d", result);

	//store queues into vkInfo->*Queue
	vkGetDeviceQueue(vkInfo->device, indices.graphicsFamily.value, 0, &vkInfo->graphicsQueue);
	vkGetDeviceQueue(vkInfo->device, indices.presentFamily.value, 0, &vkInfo->presentQueue);

	FE_ListClear(requiredDeviceExtensionsNames);
	FE_ListClear(uniqueQueueFamilies);
	FE_ListClear(queueCreateInfos);

	FE_CORE_LOG_SUCCESS("Vulkan logical device created");
}

void FE_API VulkanDestroyLogicalDevice(FE_VulkanInfo* vkInfo)
{
	vkDestroyDevice(vkInfo->device, NULL);
}
