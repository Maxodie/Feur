#include "fepch.h"
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Feur/Core/Application.h"
#include "Platform/Windows/GLFW/GLFWWindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT

#include <Nuklear/nuklear.h>
#include <Nuklear/demo/glfw_opengl4/nuklear_glfw_gl4.h>

void OpenGL_GLFW_NuklearGUILayerEvent_impl(FE_Event* event)
{
}

void OpenGL_GLFW_NuklearGUILayerRender_impl(Layer* layer)
{
	struct nk_context* context = (struct nk_context*)layer->handledInfo;
	nk_glfw3_new_frame();
	if(nk_begin(context, "Nuklear Window", nk_rect(0, 0, 500, 500), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE))
	{
		/*struct nk_vec2 rect = nk_window_get_content_region_min(context);
		struct nk_vec2 size = nk_window_get_content_region_size(context);

		struct nk_vec2 tabPos =  nk_window_get_content_region_max(context);
		struct nk_vec2 winSize = { .x = GetApp()->windowData.w, .y = GetApp()->windowData.h };


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
		*/
		//FE_CORE_LOG_DEBUG("x : %f; y : %f", rect.x, rect.y);
	}
	nk_end(context);

	nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

void OpenGL_GLFW_NuklearGUILayerOnAttach_impl(Layer* layer)
{
	GLFWwindow* window = (GLFWwindow*)GetApp()->windowData.nativeWindow;
	
	layer->handledInfo = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

	//set up font
	struct nk_font_atlas* atlas;
	nk_glfw3_font_stash_begin(&atlas);
	nk_glfw3_font_stash_end();
}

void OpenGL_GLFW_NuklearGUILayerOnDetach_impl()
{
	nk_glfw3_shutdown();
}
