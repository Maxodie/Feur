#include "fepch.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Debug/VulkanDebug.h"
#include "Platform/Vulkan/Setup/VulkanDevice.h"
#include "Platform/Vulkan/Setup/VulkanSwapChain.h"
#include "Platform/Vulkan/Setup/VulkanImageView.h"

Bool FE_API VulkanInit_impl(RendererAPIData* apiData)
{
	VulkanfeInfo* vkInfo = FE_MemoryGeneralAlloc(sizeof(VulkanfeInfo));
	FE_CORE_ASSERT(vkInfo != NULL, "Failed allocate memory for VulkanInfo");

	VulkanInitValidationLayer(vkInfo);
	VulkanInitDefaultDebug(&vkInfo->vkfeDebugger);

	CreateVulkanInstance(vkInfo);

	VulkanSetupDebugMessenger(vkInfo);
	CreateVulkanSurface(vkInfo);
	VulkanPickPhysicalDevice(vkInfo);
	VulkanCreateLogicalDevice(vkInfo);
	VulkanCreateSwapChain(vkInfo);

	VulkanCreateImageView(vkInfo);

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
	VulkanfeInfo* vkInfo = (VulkanfeInfo*)apiData->nativeInfoAPI;
	
	VulkanCleanup(vkInfo);
	FE_ListClear(vkInfo->validationLayers);
	FE_ListClear(vkInfo->deviceExtensions);
	FE_MemoryGeneralFree(vkInfo);
}