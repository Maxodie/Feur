#include "fepch.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

void FE_API Vulkan_GLFWwindowHintParameters()
{
	/*glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_SAMPLES, 4);
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

void FE_API Vulkan_GLFWsetExtentionCount(VkInstanceCreateInfo* createInfo)
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo->enabledExtensionCount = glfwExtensionCount;
	createInfo->ppEnabledExtensionNames = glfwExtensions;
}
