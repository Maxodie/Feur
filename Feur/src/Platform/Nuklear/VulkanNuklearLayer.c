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


void FE_DECL Vulkan_GLFW_NuklearGUILayerEvent_impl(FE_Event* event)
{
}

void FE_DECL Vulkan_GLFW_NuklearGUILayerRender_impl(Layer* layer)
{
	nk_glfw3_vk_new_frame();

	struct nk_context* context = (struct nk_context*)layer->handledInfo;
	if (nk_begin(context, "Nuklear Window", nk_rect(0, 0, 500, 500), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE))
	{
		struct nk_vec2 rect = nk_window_get_content_region_min(context);
		struct nk_vec2 size = nk_window_get_content_region_size(context);

		struct nk_vec2 tabPos = nk_window_get_content_region_max(context);
		struct nk_vec2 winSize = { .x = (Float32)GetApp()->windowData.w, .y = (Float32)GetApp()->windowData.h };

		struct nk_colorf background = { .r = 0.1f, .g = 0.1f, .b = 0.1f, .a = 1 };
		nk_layout_row_static(context, 30, 80, 1);
		if (nk_button_label(context, "button"))
			fprintf(stdout, "button pressed\n");

		nk_layout_row_dynamic(context, 20, 1);
		nk_label(context, "background:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(context, 25, 1);
		if (nk_combo_begin_color(context, nk_rgb_cf(background),
			nk_vec2(nk_widget_width(context), 400))) {
			nk_layout_row_dynamic(context, 120, 1);
			background = nk_color_picker(context, background, NK_RGBA);
			nk_layout_row_dynamic(context, 25, 1);
			nk_combo_end(context);
		}

		FE_CORE_LOG_DEBUG("x : %f; y : %f", rect.x, rect.y);
	}
	nk_end(context);

	FE_VulkanInfo* vkInfo = GetApp()->rendererAPIData.nativeInfoAPI;
	vkInfo->imageGUIAvailableSemaphores = nk_glfw3_vk_render(vkInfo->graphicsQueue, vkInfo->currentFrame, NULL, NK_ANTI_ALIASING_ON);
}

void FE_DECL Vulkan_GLFW_NuklearGUILayerOnAttach_impl(Layer* layer)
{
	GLFWwindow* window = GetApp()->windowData.nativeWindow;
	FE_VulkanInfo* vkInfo = GetApp()->rendererAPIData.nativeInfoAPI;
	layer->handledInfo = nk_glfw3_vk_init(window, vkInfo->instance, vkInfo->logicalDevice, vkInfo->physicalDevice.GPU, vkInfo->queueFamilyIndices.graphicsFamily.value,
		vkInfo->swapChain.imageViews.data, (Uint32)vkInfo->swapChain.imageViews.impl.count, vkInfo->swapChain.imageFormat, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

	//set up font
	struct nk_font_atlas* atlas;
	nk_glfw3_vk_font_stash_begin(&atlas);
	nk_glfw3_vk_font_stash_end(vkInfo->graphicsQueue);

	FE_CORE_LOG_SUCCESS("Vulkan Nuklear GUI Layer has been created");
}

void FE_DECL Vulkan_GLFW_NuklearGUILayerOnDetach_impl()
{
	nk_glfw3_vk_shutdown();
}
