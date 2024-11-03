#include "fepch.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

void FE_API Vulkan_GLFWwindowHintParameters()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	/*glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);*/
}

void FE_API Vulkan_GLFWgraphicsContextInit(WindowData* windowData)
{


	/*glfwMakeContextCurrent((GLFWwindow*)windowData->nativeWindow);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	FE_CORE_ASSERT(status, "Failed to initialize Glad !")

	FE_CORE_LOG_SUCCESS("   ==OpengGL GLFW Context loaded==")
	FE_CORE_LOG_SUCCESS("   Vendor: %s", (const char*)glGetString(GL_VENDOR))
	FE_CORE_LOG_SUCCESS("   Renderer: %s", (const char*)glGetString(GL_RENDERER))
	FE_CORE_LOG_SUCCESS("   Version: %s", (const char*)glGetString(GL_VERSION))*/
}

void FE_API Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData)
{
	//glfwSwapBuffers((GLFWwindow*)windowData->nativeWindow);
}

void FE_API Vulkan_GLFWsetExtention(VkInstanceCreateInfo* createInfo, const VulkanfeInfo* vkInfo)
{
	Uint32 glfwExtensionCount = 0;
	const char* const* glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	FE_List(const char* const) extensions = { 0 };
	FE_ListInit(extensions);

	FE_ListPushArray(extensions, glfwExtensions, glfwExtensionCount);
	
	if (vkInfo->enableValidationLayers) {
		const char* debugLayer = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
		FE_ListPush(extensions, debugLayer);
	}

#ifndef FE_DIST

	FE_CORE_LOG_SUCCESS("   == Vulkan GLFW required extensions ==");
	for (SizeT i = 0; i < extensions.impl.count; i++)
	{
		const char* str = extensions.data[i];
		FE_CORE_LOG_SUCCESS("   - NAME   %s", extensions.data[i]);
	}
#endif
	createInfo->enabledExtensionCount = (Uint32)extensions.impl.count;
	createInfo->ppEnabledExtensionNames = extensions.data;
}

void Vulkan_GLFWcreateSurface(VulkanfeInfo* vkInfo)
{
	VkResult success = glfwCreateWindowSurface(vkInfo->vkInstance, GetApp()->windowData.nativeWindow, NULL, &vkInfo->surface);
	FE_CORE_ASSERT(success == VK_SUCCESS, "failed to create window surface!");
}
