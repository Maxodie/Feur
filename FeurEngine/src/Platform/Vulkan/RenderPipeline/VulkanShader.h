#pragma once
#include <vulkan/vulkan.h>

struct FE_VulkanInfo;

typedef enum FE_VulkanShaderKind {
	VERTEX_SHADER,
	FRAGMENT_SHADER
} FE_VulkanShaderKind;

void VulkanCreateShaderCompiler(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyShaderCompiler(struct FE_VulkanInfo* vkInfo);
VkShaderModule VulkanCreateShaderModule(struct FE_VulkanInfo* vkInfo, const char* shaderName, FE_VulkanShaderKind kind);
