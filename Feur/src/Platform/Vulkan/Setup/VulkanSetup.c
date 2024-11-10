#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"

void VulkanCreateInstance(FE_VulkanInfo* vkInfo)
{
	//Init validation layers
	if (vkInfo->debugger.validationLayer.enableValidationLayers && !VulkanCheckValidationLayerSupport(&vkInfo->debugger.validationLayer))
	{
		FE_ListClear(vkInfo->debugger.validationLayer.validationLayers);
		FE_CORE_LOG_ERROR("Vulkan validation layers are enabled but not available. Therefore disabling validation layers");
		vkInfo->debugger.validationLayer.enableValidationLayers = FALSE;
	}

	//Create instance data
	VkApplicationInfo appInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "Vulkan Feur App",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "Feur Engine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	VkInstanceCreateInfo createInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appInfo,
#ifdef FE_PLATFORM_MACOS
		.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
#endif
	};

	//setup validation layers/window extensions into the instance data
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = { 0 };
	if (vkInfo->debugger.validationLayer.enableValidationLayers)
	{
		createInfo.enabledLayerCount = (Uint32)vkInfo->debugger.validationLayer.validationLayers.impl.count;
		createInfo.ppEnabledLayerNames = vkInfo->debugger.validationLayer.validationLayers.data;
		VulkanPopulateDebugMessenger(&debugCreateInfo, vkInfo);
		createInfo.pNext = &debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = NULL;
		createInfo.pNext = VK_NULL_HANDLE;
	}

	//window extension
	FE_List(const char* const) createInfoExtensions = { 0 };
	FE_ListInit(createInfoExtensions);

#ifdef FE_PLATFORM_MACOS
	FE_ListPushValue(createInfoExtensions, const char* const, "VK_KHR_portability_enumeration");
#endif

	if (vkInfo->debugger.validationLayer.enableValidationLayers) {
		FE_ListPushValue(createInfoExtensions,const char* const, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	switch (GetWindowAPI()->API_Type)
	{
	case FE_WINDOW_API_GLFW:
		Vulkan_GLFWsetExtention(&createInfo, vkInfo, &createInfoExtensions);
		break;
	default:
		FE_CORE_ASSERT(FALSE, "failed to set extention count, Window API not supported yet");
		return;
		break;
	}

	//Get vulkan extensions
	Uint32 extensionCount;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* extensions = FE_MemoryGeneralAlloc(extensionCount * sizeof(VkExtensionProperties));

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
	VkResult result = vkCreateInstance(&createInfo, NULL, &vkInfo->instance);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create vulkan instance - %d", result);
	FE_ListClear(createInfoExtensions);

	FE_CORE_LOG_SUCCESS("Vulkan instance created");
}

void VulkanDestroyInstance(FE_VulkanInfo* vkInfo)
{
	vkDestroyInstance(vkInfo->instance, NULL);
}

void VulkanCreateSemaphoresAndFences(FE_VulkanInfo* vkInfo)
{
	Bool resultFailed = FALSE;
	// Semaphores and fences
	vkInfo->imageAvailableSemaphores = FE_MemoryGeneralAlloc(sizeof(VkSemaphore) * vkInfo->swapChain.maxFramesInFlight);
	vkInfo->queueCompleteSemaphores = FE_MemoryGeneralAlloc(sizeof(VkSemaphore) * vkInfo->swapChain.maxFramesInFlight);
	vkInfo->inFlightFences = FE_MemoryGeneralAlloc(sizeof(VkFence) * vkInfo->swapChain.maxFramesInFlight);

	VkSemaphoreCreateInfo semaphoreCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
			.flags = 0,
			.pNext = VK_NULL_HANDLE,
	};

	VkFenceCreateInfo fenceCreateInfo = {
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.flags = VK_FENCE_CREATE_SIGNALED_BIT,
			.pNext = VK_NULL_HANDLE,
	};

	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		resultFailed = vkCreateSemaphore(vkInfo->logicalDevice, &semaphoreCreateInfo, NULL, &vkInfo->imageAvailableSemaphores[i]) != VK_SUCCESS;
		resultFailed += vkCreateSemaphore(vkInfo->logicalDevice, &semaphoreCreateInfo, NULL, &vkInfo->queueCompleteSemaphores[i]) != VK_SUCCESS;
		resultFailed += vkCreateFence(vkInfo->logicalDevice, &fenceCreateInfo, NULL, &vkInfo->inFlightFences[i]) != VK_SUCCESS;

		FE_CORE_ASSERT(resultFailed == FALSE, "Vulkan failed to create semaphores and fences");
	}

	FE_CORE_ASSERT(resultFailed == FALSE, "Vulkan failed to create semaphores and fences");

	FE_CORE_LOG_SUCCESS("Vulkand semaphores and fences successfuly created");
}

void VulkanDestroySemaphoresAndFences(FE_VulkanInfo* vkInfo)
{
	if (vkInfo->swapChain.maxFramesInFlight == 0) return;

	for (Uint32 i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		vkDestroySemaphore(vkInfo->logicalDevice, vkInfo->imageAvailableSemaphores[i], NULL);
		vkDestroySemaphore(vkInfo->logicalDevice, vkInfo->queueCompleteSemaphores[i], NULL);
		vkDestroyFence(vkInfo->logicalDevice, vkInfo->inFlightFences[i], NULL);
	}

	FE_MemoryGeneralFree(vkInfo->imageAvailableSemaphores);
	FE_MemoryGeneralFree(vkInfo->queueCompleteSemaphores);
	FE_MemoryGeneralFree(vkInfo->inFlightFences);
}
