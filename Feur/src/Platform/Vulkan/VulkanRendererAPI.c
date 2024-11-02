#include "fepch.h"
#include "Platform/Vulkan/VulkanSetup.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"

Bool FE_API VulkanInit_impl(RendererAPIData* apiData)
{
	VulkanInfo* vkInfo = FE_MemoryGeneralAlloc(sizeof(VulkanInfo));

	if (vkInfo == NULL)
	{
		FE_CORE_LOG_ERROR("Failed allocate memory for VulkanInfo");
		return FALSE;
	}

	VulkanInitValidationLayer(vkInfo);

	vkInfo->vkfeDebugger.enableFullVulkanDebugMsg = TRUE;

	if (!CreateVulkanInstance(vkInfo))
	{
		FE_CORE_LOG_ERROR("Failed to create vulkanInstance");
		return FALSE;
	}

	VulkanSetupDebugMessenger(vkInfo);

	apiData->nativeInfoAPI = vkInfo;
	return TRUE;
}

void FE_API VulkanSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
	//glViewport(x, y, width, height);
}

void FE_API VulkanClearScreenColor_impl()
{
	//glClearColor(100, 0, 100, 255);
}

void FE_API VulkanClear_impl()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FE_API VulkanDrawIndex_impl()
{
}

void FE_API VulkanShutdown_impl(RendererAPIData* apiData)
{
	VulkanInfo* vkInfo = (VulkanInfo*)apiData->nativeInfoAPI;
	
	VulkanDestroyDebugMessenger(vkInfo);
	VulkanCleanup(vkInfo->vkInstance);
	FE_MemoryGeneralFree(vkInfo);
}