#pragma once
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.h>
#include "Platform/Vulkan/Setup/VulkanStructures.h"


void FE_API CreateVulkanInstance(FE_VulkanInfo* vkInfo);
void FE_API VulkanCleanup(FE_VulkanInfo* vkInfo);

void FE_API CleanupVulkanSurface(FE_VulkanInfo* vkInfo);