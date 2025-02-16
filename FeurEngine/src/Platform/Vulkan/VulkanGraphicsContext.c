#include "fepch.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

void Vulkan_GLFWwindowHintParameters()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Vulkan_GLFWgraphicsContextInit(WindowData* windowData)
{
}

void Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData)
{
}

void Vulkan_GLFWsetExtention(VkInstanceCreateInfo* createInfo, const FE_VulkanInfo* vkInfo, void* extensionsFeList)
{
	Uint32 glfwExtensionCount = 0;
	const char* const* glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	FE_List(const char* const)* extensions = extensionsFeList;

	FE_ListPushArray(*extensions, glfwExtensions, glfwExtensionCount);
	
#ifndef FE_DIST

	FE_CORE_LOG_SUCCESS("   == Vulkan GLFW required extensions ==");
	for (SizeT i = 0; i < extensions->impl.count; i++)
	{
		const char* str = extensions->data[i];
		FE_CORE_LOG_SUCCESS("   - NAME   %s", extensions->data[i]);
	}
#endif
	createInfo->enabledExtensionCount = (Uint32)extensions->impl.count;
	createInfo->ppEnabledExtensionNames = extensions->data;
}

void CreateVulkanSurface(FE_VulkanInfo* vkInfo)
{
	switch (GetWindowAPI()->API_Type)
	{
	case FE_WINDOW_API_GLFW:
		Vulkan_GLFWcreateSurface(vkInfo);
		break;
	default:
		FE_CORE_ASSERT(FALSE, "failed to create vulkan surface, Window API not supported yet");
		return;
		break;
	}
}

void Vulkan_GLFWcreateSurface(FE_VulkanInfo* vkInfo)
{
	VkResult result = glfwCreateWindowSurface(vkInfo->instance, GetApp()->windowData.nativeWindow, NULL, &vkInfo->surface);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create window surface! - %d", result);
}

void VulkanCleanupSurface(FE_VulkanInfo* vkInfo)
{
	vkDestroySurfaceKHR(vkInfo->instance, vkInfo->surface, NULL);
}