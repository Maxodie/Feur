#pragma once

void VulkanInitImageViewsDefaultData(struct FE_VulkanInfo* vkInfo);
void VulkanShutdownImageViewsDefaultData(struct FE_VulkanInfo* vkInfo);
void VulkanCreateImageView(struct FE_VulkanInfo* vkInfo); 
void VulkanDestroyImageView(struct FE_VulkanInfo* vkInfo);