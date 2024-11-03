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
	if (messageSeverity < VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		FE_CORE_LOG_DEBUG("Vulkan Validation layer: %s", pCallbackData->pMessage);
	}
	else if(messageSeverity > VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		FE_CORE_LOG_ERROR("Vulkan Validation layer: %s", pCallbackData->pMessage);
	}
	else
	{
		FE_CORE_LOG_WARNING("Vulkan Validation layer: %s", pCallbackData->pMessage);
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) 
{
	VulkanfeDebugger* vkfeDebugger = pUserData;
	if (vkfeDebugger->enableFullVulkanDebugMsg || messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		VulkanShowDebug(messageSeverity, pCallbackData);
	}

	return VK_FALSE;
}

void FE_API VulkanInitDefaultDebug(VulkanfeDebugger* vkfeDebugger)
{
	vkfeDebugger->enableFullVulkanDebugMsg = FALSE;
}

void FE_API VulkanPopulateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT* createInfo, const VulkanfeInfo* vkInfo)
{
	createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo->pfnUserCallback = VulkanDebugCallback;
	createInfo->pUserData = &vkInfo->vkfeDebugger;
}

void FE_API VulkanSetupDebugMessenger(VulkanfeInfo* vkInfo)
{
	if (!vkInfo->enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	VulkanPopulateDebugMessenger(&createInfo, vkInfo);
	
	VkResult success = CreateDebugUtilsMessengerEXT(vkInfo->vkInstance, &createInfo, NULL, &vkInfo->vkfeDebugger.callback);
	FE_CORE_ASSERT(success == VK_SUCCESS, "Vulkan Debug message could not be created");
}

void FE_API VulkanDestroyDebugMessenger(VulkanfeInfo* vkInfo)
{
	if (vkInfo->enableValidationLayers)
	{
		DestroyDebugUtilsMessengerEXT(vkInfo->vkInstance, vkInfo->vkfeDebugger.callback, NULL);
	}
}
