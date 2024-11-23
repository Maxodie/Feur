#include "fepch.h"
#include "Platform/Nuklear/OpenGLNuklearLayer.h"

#include <glad/glad.h>

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

#define NK_GLFW_GL4_IMPLEMENTATION

#include <Nuklear/nuklear.h>
#include "NuklearGlfwGl4.h"

void FE_DECL OpenGL_GLFW_NuklearGUIInit_impl(NuklearGUIInterface* interface)
{
	GLFWwindow* window = (GLFWwindow*)GetApp()->windowData.nativeWindow;

	interface->handle = nk_glfw3_gl4_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

	//set up font
	struct nk_font_atlas* atlas;
	nk_glfw3_gl4_font_stash_begin(&atlas);
	nk_glfw3_gl4_font_stash_end();
}

void FE_DECL OpenGL_GLFW_NuklearGUIEvent_impl(FE_Event* event)
{
}

void FE_DECL OpenGL_GLFW_NuklearGUIEndRender_impl(NuklearGUIInterface* interface)
{
	struct nk_context* context = (struct nk_context*)interface->handle;
	nk_glfw3_gl4_new_frame();
	if (nk_begin(context, "Nuklear Window", nk_rect(0, 0, 500, 500), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE))
	{
		struct nk_vec2 rect = nk_window_get_content_region_min(context);
		struct nk_vec2 size = nk_window_get_content_region_size(context);

		struct nk_vec2 tabPos =  nk_window_get_content_region_max(context);
		struct nk_vec2 winSize = { .x = (Float32)GetApp()->windowData.w, .y = (Float32)GetApp()->windowData.h };


		if (size.x > winSize.x - 20)
		{
			struct nk_vec2 newSize = { .x = winSize.x - 20, .y = size.y + 29 };
			nk_window_set_size(context, "Nuklear Window", newSize);
		}
		if (size.y > winSize.y - 50)
		{
			struct nk_vec2 newSize = { .x = size.x + 4, .y = winSize.y - 50 };
			nk_window_set_size(context, "Nuklear Window", newSize);
		}

		if (tabPos.x > winSize.x - 6 )
		{
			struct nk_vec2 newPos = { .x = winSize.x - size.x - 16, .y = rect.y - 29};
			nk_window_set_position(context, "Nuklear Window", newPos);
		}
		if (tabPos.y > winSize.y)
		{
			struct nk_vec2 newPos = { .x = rect.x - 4, .y = winSize.y - size.y - 29 };
			nk_window_set_position(context, "Nuklear Window", newPos);
		}
		if (rect.x < 0)
		{
			struct nk_vec2 newPos = { .x = 0, .y = rect.y - 29};
			nk_window_set_position(context, "Nuklear Window", newPos);
		}
		if (rect.y < 0)
		{
			struct nk_vec2 newPos = { .x = rect.x - 6, .y = 0 };
			nk_window_set_position(context, "Nuklear Window", newPos);
		}
		
		FE_CORE_LOG_DEBUG("x : %f; y : %f", rect.x, rect.y);
	}
	nk_end(context);

	nk_glfw3_gl4_render(NK_ANTI_ALIASING_ON);
}


void FE_DECL OpenGL_GLFW_NuklearGUIShutdown_impl()
{
	nk_glfw3_gl4_shutdown();
}
