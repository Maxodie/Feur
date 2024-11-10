#pragma once
#include <vulkan/vulkan.h>

typedef enum VulkanShaderKind {
	VERTEX_SHADER, 
	FRAGMENT_SHADER 
} VulkanShaderKind;

void VulkanCreateShaderCompiler(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyShaderCompiler(struct FE_VulkanInfo* vkInfo);
VkShaderModule VulkanCreateShaderModule(struct FE_VulkanInfo* vkInfo, const char* shaderName, VulkanShaderKind kind);