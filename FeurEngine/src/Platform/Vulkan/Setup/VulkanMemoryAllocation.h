#pragma once

struct FE_VulkanInfo;

void VulkanCreateAllocator(struct FE_VulkanInfo* vkInfo);
void VulkanDestroyAllocator(struct FE_VulkanInfo* vkInfo);
