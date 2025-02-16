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

void FE_DECL OpenGL_GLFW_NuklearGUIEndRender_impl()
{
	nk_glfw3_gl4_new_frame();
	nk_glfw3_gl4_render(NK_ANTI_ALIASING_ON);
}


void FE_DECL OpenGL_GLFW_NuklearGUIShutdown_impl()
{
	nk_glfw3_gl4_shutdown();
}
