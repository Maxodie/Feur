#pragma once

struct FE_VulkanValidationLayer;

void VulkanInitValidationLayer(struct FE_VulkanValidationLayer* vkValidationLayer);
Bool VulkanCheckValidationLayerSupport(const struct FE_VulkanValidationLayer* vkValidationLayer);
