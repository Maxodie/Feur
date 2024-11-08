#pragma once

void FE_API VulkanInitValidationLayer(struct FE_VulkanValidationLayer* vkValidationLayer);
Bool FE_API VulkanCheckValidationLayerSupport(const struct FE_VulkanValidationLayer* vkValidationLayer);