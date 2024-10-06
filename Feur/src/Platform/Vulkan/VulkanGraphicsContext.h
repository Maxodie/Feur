#pragma once

void FE_API Vulkan_GLFWwindowHintParameters();
void FE_API Vulkan_GLFWgraphicsContextInit(WindowData* windowData);
void FE_API Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData);

void FE_API Vulkan_GLFWsetExtentionCount(struct VkInstanceCreateInfo* createInfo);