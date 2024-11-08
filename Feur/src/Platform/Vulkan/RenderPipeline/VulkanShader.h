#pragma once
#include <vulkan/vulkan.h>

typedef enum VulkanShaderKind {
	VERTEX_SHADER, 
	FRAGMENT_SHADER 
} VulkanShaderKind;

void FE_API VulkanCreateShaderCompiler(struct FE_VulkanInfo* vkInfo);
void FE_API VulkanDestroyShaderCompiler(struct FE_VulkanInfo* vkInfo);
VkShaderModule FE_API VulkanCreateShaderModule(struct FE_VulkanInfo* vkInfo, const char* shaderName, VulkanShaderKind kind);