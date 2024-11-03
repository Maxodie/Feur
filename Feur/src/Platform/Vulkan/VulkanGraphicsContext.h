#pragma once

//GLFW
void FE_API Vulkan_GLFWwindowHintParameters();
void FE_API Vulkan_GLFWgraphicsContextInit(WindowData* windowData);
void FE_API Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData);


void FE_API Vulkan_GLFWsetExtention(struct VkInstanceCreateInfo* createInfo, const struct VulkanfeInfo* vkInfo);

void FE_API Vulkan_GLFWcreateSurface(struct VulkanfeInfo* vkInfo);