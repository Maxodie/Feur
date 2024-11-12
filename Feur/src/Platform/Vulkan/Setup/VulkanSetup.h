#pragma once
#include <vulkan/vulkan.h>
#include <shaderc/shaderc.h>
#include <vk_mem_alloc.h>
#include "Platform/Vulkan/Setup/VulkanStructures.h"

void VulkanCreateInstance(FE_VulkanInfo* vkInfo);
void VulkanDestroyInstance(FE_VulkanInfo* vkInfo);

void VulkanCreateSemaphoresAndFences(FE_VulkanInfo* vkInfo);
void VulkanDestroySemaphoresAndFences(FE_VulkanInfo* vkInfo);