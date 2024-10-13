#include "fepch.h"
#include "Platform/Vulkan/VulkanSetup.h"
#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/VulkanValidationLayer.h"

Bool FE_API CreateVulkanInstance(VulkanInfo* vkInfo)
{
	if (vkInfo->enableValidationLayers && !VulkanCheckValidationLayerSupport(vkInfo))
	{
		FE_CORE_LOG_ERROR("VulkanSetup.c : CreateVulkanInstance : Vulkan validation layers are enabled but not available");
	}

	VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Vulkan Feur App",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "Feur Engine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_0
	};

	VkInstanceCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
	};

	if (vkInfo->enableValidationLayers)
	{
		createInfo.enabledExtensionCount = vkInfo->validationsCount;
		createInfo.ppEnabledExtensionNames = vkInfo->validationLayers;
	}
	else
	{
		createInfo.enabledExtensionCount = 0;
	}

	switch (GetWindowAPI()->API_Type)
	{
	case FE_WINDOW_API_GLFW:
		Vulkan_GLFWsetExtentionCount(&createInfo);
		break;
	default:
		FE_CORE_LOG_ERROR("VulkanSetup.c : CreateVulkanInstance : failed to set extention count");
		return FALSE;
		break;
	}

	createInfo.enabledLayerCount = 0;

	Uint32 extensionCount;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* extensions = malloc(extensionCount * sizeof(VkExtensionProperties));
	if (extensions == NULL)
	{
		FE_CORE_LOG_ERROR("VulkanSetup.c : CreateVulkanInstance : failed to allocate memory for extensions properties");
		return FALSE;
	}

	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);

	FE_CORE_LOG_SUCCESS("   == Vulkan Extensions Supported ==");

	for (Uint32 i = 0; i < extensionCount; i++) {
		FE_CORE_LOG_SUCCESS("   - NAME   %s || VERSION   %d", (const char*)extensions[i].extensionName, extensions[i].specVersion);
	}

	free(extensions);

	if (vkCreateInstance(&createInfo, NULL, &vkInfo->vkInstance) != VK_SUCCESS) {
		FE_CORE_LOG_ERROR("VulkanSetup.c : CreateVulkanInstance : failed to create vulkan instance");
		return FALSE;
	}

	return TRUE;
}

void FE_API VulkanCleanup(VkInstance* vkInstance)
{
	vkDestroyInstance(*vkInstance, NULL);
}
