#include "fepch.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

void VulkanInitValidationLayer(FE_VulkanValidationLayer* vkValidationLayer)
{
#ifdef FE_DEBUG
	FE_ListInit(vkValidationLayer->validationLayers);
	FE_ListPushValue(vkValidationLayer->validationLayers, const char*, "VK_LAYER_KHRONOS_validation");
	vkValidationLayer->enableValidationLayers = TRUE;
#else
	vkValidationLayer->enableValidationLayers = FALSE;
#endif
}

Bool VulkanCheckValidationLayerSupport(const FE_VulkanValidationLayer* vkValidationLayer)
{
	Uint32 availableLayerCount;
	vkEnumerateInstanceLayerProperties(&availableLayerCount, NULL);

	VkLayerProperties* availableLayers = FE_MemoryGeneralAlloc(availableLayerCount * sizeof(VkLayerProperties));
	//if (availableLayers == NULL)
	//{
	//	FE_CORE_LOG_ERROR("failed to allocate memory for availableLayers");
	//	return FALSE;
	//}

	vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers);

	Bool sucess = TRUE;
	Bool layerFound;
	Uint32 j;

	for (Uint32 i = 0; i < vkValidationLayer->validationLayers.impl.count; i++) {
		layerFound = FALSE;

		for (j = 0; j < availableLayerCount; j++) {
			if (strcmp(vkValidationLayer->validationLayers.data[i], availableLayers[j].layerName) == 0)
			{
				layerFound = TRUE;
				break;
			}
		}

		if (!layerFound)
		{
			sucess = FALSE;
			break;
		}
	}

#ifndef FE_DIST
	FE_CORE_LOG_SUCCESS("   == Vulkan Validation Layers Supported ==");
	for (Uint32 i = 0; i < availableLayerCount; i++) {
		FE_CORE_LOG_SUCCESS("   - NAME   %s", (const char*)availableLayers[i].layerName);
	}

	if (!sucess)
	{
		FE_CORE_LOG_ERROR("   == Vulkan Validation Layers not found  ==");
	}

	
#endif // !FE_DIST

	FE_MemoryGeneralFree(availableLayers);

	return sucess;
}