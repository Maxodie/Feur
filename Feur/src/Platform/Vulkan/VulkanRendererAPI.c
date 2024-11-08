#include "fepch.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"

#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"

#include "Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.h"

Bool FE_API VulkanInit_impl(RendererAPIData* apiData)
{
	FE_VulkanInfo* vkInfo = FE_MemoryGeneralAlloc(sizeof(FE_VulkanInfo));
	FE_CORE_ASSERT(vkInfo != NULL, "Failed allocate memory for VulkanInfo");

	VulkanInitValidationLayer(&vkInfo->validationLayer);

	CreateVulkanInstance(vkInfo);

	if (vkInfo->validationLayer.enableValidationLayers)
	{
		VulkanCreateDebugMessenger(vkInfo);
	}

	CreateVulkanSurface(vkInfo);
	VulkanInitDefaultDeviceSelection(vkInfo);
	VulkanPickPhysicalDevice(vkInfo);
	VulkanCreateLogicalDevice(vkInfo);
	VulkanCreateSwapChain(vkInfo);

	//VulkanCreateImageView(vkInfo);
	//VulkanCreateGraphicsPipeline(vkInfo);

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
	FE_VulkanInfo* vkInfo = (FE_VulkanInfo*)apiData->nativeInfoAPI;
	
	//VulkanCleanupGraphicsPipeline(vkInfo);
	//VulkanDestroyImageView(vkInfo);
	VulkanDestroySwapChain(vkInfo);
	VulkanDestroyLogicalDevice(vkInfo);
	CleanupVulkanSurface(vkInfo);

	if (vkInfo->validationLayer.enableValidationLayers)
	{
		VulkanCleanupDebugMessenger(vkInfo);
	}

	VulkanCleanup(vkInfo);

	if (vkInfo->validationLayer.enableValidationLayers)
	{
		FE_ListClear(vkInfo->validationLayer.validationLayers);
	}

	FE_MemoryGeneralFree(vkInfo);
}