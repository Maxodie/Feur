#include "fepch.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include <vulkan/vulkan.h>

VkResult FE_API CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback)
{	
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != NULL) 
	{
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else 
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void FE_API DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator)
{
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL) 
	{
		func(instance, callback, pAllocator);
	}
}

static void VulkanShowDebug(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
{
	switch (messageSeverity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		FE_CORE_LOG_ERROR("Vulkan Validation layer: %s", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		FE_CORE_LOG_WARNING("Vulkan Validation layer: %s", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		FE_CORE_LOG_DEBUG("Vulkan Validation layer: %s", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		FE_CORE_LOG_DEBUG("Vulkan Validation layer: %s", pCallbackData->pMessage);
		break;
	default:
		FE_CORE_LOG_DEBUG("Vulkan Validation layer: %s", pCallbackData->pMessage);
		break;
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) 
{
	FE_VulkanDebugger* debugger = pUserData;
	if (debugger->validationLayer.enableValidationLayers && debugger->enableFullVulkanDebugMsg || messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		VulkanShowDebug(messageSeverity, pCallbackData);
	}

	return VK_FALSE;
}

void FE_API VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, FE_VulkanInfo* vkInfo)
{
	createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	
	createInfo->messageSeverity =	VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | 
									VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
									VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
									VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	
	createInfo->messageType =	VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
								VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
								VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
								VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;

	createInfo->pfnUserCallback = VulkanDebugCallback;
	createInfo->pUserData = &vkInfo->debugger;
}

void FE_API VulkanCreateDebugMessenger(FE_VulkanInfo* vkInfo)
{
	FE_CORE_LOG_SUCCESS("Initializing Vulkan debugger...");

	//default variables
	vkInfo->debugger.enableFullVulkanDebugMsg = TRUE;
	//

	VkDebugUtilsMessengerCreateInfoEXT createInfo = { 0 };
	VulkanPopulateDebugMessenger(&createInfo, vkInfo);
	
	VkResult result = CreateDebugUtilsMessengerEXT(vkInfo->instance, &createInfo, NULL, &vkInfo->debugger.callback);
	FE_CORE_ASSERT(result == VK_SUCCESS, "Vulkan Debug message could not be created - %d", result);

	FE_CORE_LOG_SUCCESS("Vulkan debugger Initialized");
}

void FE_API VulkanCleanupDebugMessenger(FE_VulkanInfo* vkInfo)
{
	if (vkInfo->debugger.validationLayer.enableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(vkInfo->instance, vkInfo->debugger.callback, NULL);
		FE_CORE_LOG_SUCCESS("Shuting down the vulkan debugger");
	}
}
