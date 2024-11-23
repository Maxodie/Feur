#include "fepch.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <shaderc/shaderc.h>
#include "Platform/Vulkan/Setup/VulkanStructures.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT

#define NK_GLFW_VULKAN_IMPLEMENTATION

#include <Nuklear/nuklear.h>
#include "NuklearGlfwVulkan.h"


void FE_DECL Vulkan_GLFW_NuklearGUIEvent_impl(FE_Event* event)
{
}

void FE_DECL Vulkan_GLFW_NuklearGUIBeginRender_impl(NuklearGUIInterface* interface)
{
	nk_glfw3_vk_new_frame();
}

void FE_DECL Vulkan_GLFW_NuklearGUIEndRender_impl(NuklearGUIInterface* interface)
{
	FE_VulkanInfo* vkInfo = GetApp()->rendererAPIData.nativeInfoAPI;
	nk_glfw3_vk_render(vkInfo->cmdBuffers[vkInfo->currentFrame], NK_ANTI_ALIASING_ON);
}

void FE_DECL Vulkan_GLFW_NuklearGUIInit_impl(NuklearGUIInterface* interface)
{
	GLFWwindow* window = GetApp()->windowData.nativeWindow;
	FE_VulkanInfo* vkInfo = GetApp()->rendererAPIData.nativeInfoAPI;
	interface->handle = nk_glfw3_vk_init(window, vkInfo->instance, vkInfo->logicalDevice, vkInfo->physicalDevice.GPU, vkInfo->queueFamilyIndices.graphicsFamily.value,
		vkInfo->swapChain.imageViews.data, (Uint32)vkInfo->swapChain.imageViews.impl.count, vkInfo->swapChain.imageFormat, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

	//set up font
	struct nk_font_atlas* atlas;
	nk_glfw3_vk_font_stash_begin(&atlas);
	nk_glfw3_vk_font_stash_end(vkInfo->graphicsQueue);

	FE_CORE_LOG_SUCCESS("Vulkan Nuklear GUI Layer has been created");
}

void FE_DECL Vulkan_GLFW_NuklearGUIShutdown_impl()
{
	nk_glfw3_vk_shutdown();
}

void FE_DECL Vulkan_GLFW_NuklearGUIOnWindowResize_impl(Uint32 width, Uint32 height)
{
	nk_glfw3_resize(width, height);
}
