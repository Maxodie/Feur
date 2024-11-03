#include "fepch.h"
#include "Platform/Vulkan/Debug/VulkanValidationLayer.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

void FE_API VulkanInitValidationLayer(VulkanfeInfo* vkInfo)
{
	FE_ListInit(vkInfo->validationLayers);
	const char* layer = "VK_LAYER_KHRONOS_validation";
	FE_ListPush(vkInfo->validationLayers, layer);

#ifdef FE_DEBUG
	vkInfo->enableValidationLayers = TRUE;
#else
	vkInfo->enableValidationLayers = FALSE;
#endif
}

Bool FE_API VulkanCheckValidationLayerSupport(const VulkanfeInfo* vkInfo)
{
	Uint32 availableLayerCount;
	vkEnumerateInstanceLayerProperties(&availableLayerCount, NULL);

	VkLayerProperties* availableLayers;
	 availableLayers = FE_MemoryGeneralAlloc(availableLayerCount * sizeof(VkLayerProperties));
	//if (availableLayers == NULL)
	//{
	//	FE_CORE_LOG_ERROR("failed to allocate memory for availableLayers");
	//	return FALSE;
	//}

	vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers);

	Bool sucess = TRUE;
	Bool layerFound;
	Uint32 j;

	for (Uint32 i = 0; i < vkInfo->validationLayers.impl.count; i++) {
		layerFound = FALSE;

		for (j = 0; j < availableLayerCount; j++) {
			if (strcmp(vkInfo->validationLayers.data[i], availableLayers[j].layerName))
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

	FE_MemoryGeneralFree(availableLayers);

	return sucess;
}