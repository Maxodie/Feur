#pragma once

struct FE_VulkanInfo;
struct VkInstanceCreateInfo;

void CreateVulkanSurface(struct FE_VulkanInfo* vkInfo);

//GLFW
void Vulkan_GLFWwindowHintParameters();
void Vulkan_GLFWgraphicsContextInit(WindowData* windowData);
void Vulkan_GLFWgraphicsContextSwapBuffers(WindowData* windowData);


void Vulkan_GLFWsetExtention(struct VkInstanceCreateInfo* createInfo, const struct FE_VulkanInfo* vkInfo, void* extensionsFeList);

void Vulkan_GLFWcreateSurface(struct FE_VulkanInfo* vkInfo);
void VulkanCleanupSurface(struct FE_VulkanInfo* vkInfo);
