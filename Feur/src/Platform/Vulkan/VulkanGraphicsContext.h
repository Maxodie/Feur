#pragma once

void FE_API CreateVulkanSurface(struct FE_VulkanInfo* vkInfo);

//GLFW
void FE_API Vulkan_GLFWwindowHintParameters();
void FE_API Vulkan_GLFWgraphicsContextInit(WindowData* windowData);
void FE_API Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData);


void FE_API Vulkan_GLFWsetExtention(struct VkInstanceCreateInfo* createInfo, const struct FE_VulkanInfo* vkInfo, void* extensionsFeList);

void FE_API Vulkan_GLFWcreateSurface(struct FE_VulkanInfo* vkInfo);