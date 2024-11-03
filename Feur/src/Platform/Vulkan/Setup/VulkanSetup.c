#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"

Bool FE_API CreateVulkanInstance(VulkanfeInfo* vkInfo)
{
	//Init validation layers
	if (vkInfo->enableValidationLayers && !VulkanCheckValidationLayerSupport(vkInfo))
	{
		FE_CORE_ASSERT(FALSE, "Vulkan validation layers are enabled but not available");
	}

	//Create instance data
	VkApplicationInfo appInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Vulkan Feur App",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "Feur Engine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_0
	};

	VkInstanceCreateInfo createInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
	};

	//setup validation layers/window extensions into the instance data
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { 0 };
	if (vkInfo->enableValidationLayers)
	{
		createInfo.enabledLayerCount = (Uint32)vkInfo->validationLayers.impl.count;
		createInfo.ppEnabledLayerNames = vkInfo->validationLayers.data;
		VulkanPopulateDebugMessenger(&debugCreateInfo, vkInfo);
		createInfo.pNext = &debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = NULL;
	}

	switch (GetWindowAPI()->API_Type)
	{
	case FE_WINDOW_API_GLFW:
		Vulkan_GLFWsetExtention(&createInfo, vkInfo);
		break;
	default:
		FE_CORE_ASSERT(FALSE, "failed to set extention count");
		return FALSE;
		break;
	}

	createInfo.enabledLayerCount = 0;

	//Get vulkan extensions
	Uint32 extensionCount;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* extensions = FE_MemoryGeneralAlloc(extensionCount * sizeof(VkExtensionProperties));
	//if (extensions == NULL)
	//{
	//	FE_CORE_ASSERT(FALSE, "failed to allocate memory for extensions properties");
	//	return FALSE;
	//}

	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);

#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan Extensions Supported ==");

	for (Uint32 i = 0; i < extensionCount; i++) 
	{
		FE_CORE_LOG_SUCCESS("   - NAME   %s || VERSION   %d", (const char*)extensions[i].extensionName, extensions[i].specVersion);
	}
#endif // !FE_DIST

	FE_MemoryGeneralFree(extensions);

	//create instance
	if (vkCreateInstance(&createInfo, NULL, &vkInfo->vkInstance) != VK_SUCCESS) 
	{
		FE_CORE_ASSERT(FALSE, "failed to create vulkan instance");
		return FALSE;
	}

	return TRUE;
}

void FE_API VulkanCleanup(VulkanfeInfo* vkInfo)
{
	vkDestroyDevice(vkInfo->device, NULL);
	VulkanDestroyDebugMessenger(vkInfo);
	vkDestroyInstance(vkInfo->vkInstance, NULL);
}
