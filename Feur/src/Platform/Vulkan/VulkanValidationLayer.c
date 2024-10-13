#include "fepch.h"
#include "Platform/Vulkan/VulkanValidationLayer.h"
#include "Platform/Vulkan/VulkanSetup.h"

void FE_API VulkanInitValidationLayer(VulkanInfo* vkInfo)
{
	vkInfo->validationLayers[0] = "VK_LAYER_KHRONOS_validation";
	vkInfo->validationsCount = 1;

#ifdef FE_DEBUG
	vkInfo->enableValidationLayers = TRUE;
#else
	vkInfo->enableValidationLayers = FALSE;
#endif
}

Bool FE_API VulkanCheckValidationLayerSupport(VulkanInfo* vkInfo)
{
	Uint32 availableLayerCount;
	vkEnumerateInstanceLayerProperties(&availableLayerCount, NULL);
	VkLayerProperties* availableLayers = malloc(availableLayerCount * sizeof(VkLayerProperties));
	if (availableLayers == NULL)
	{
		FE_CORE_LOG_ERROR("VulkanValidationLayer.c : VulkanCheckValidationLayerSupport : failed to allocate memory for availableLayers");
		return FALSE;
	}

	vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers);


	Bool sucess = TRUE;

	for (Uint32 i = 0; i < vkInfo->validationsCount; i++) {
		Bool layerFound = FALSE;

		for (Uint32 j = 0; j < availableLayerCount; j++) {
			if (strcmp(vkInfo->validationLayers[i], availableLayers[j].layerName))
			{
				layerFound = TRUE;
			}
		}

		if (!layerFound)
		{
			sucess = FALSE;
			break;
		}
	}

#ifndef FE_DIST
	if (sucess)
	{
		FE_CORE_LOG_SUCCESS("   == Vulkan Validation Layers Supported ==");
		for (Uint32 i = 0; i < availableLayerCount; i++) {
			FE_CORE_LOG_SUCCESS("   - NAME   %s", (const char*)availableLayers[i].layerName);
		}
	}
#endif // !FE_DIST


	free(availableLayers);
	return sucess;
}
