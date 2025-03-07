#include "fepch.h"
#include "Platform/OpenGL/OpenGLRendererAPIimpl.h"

#include <glad/glad.h>

Bool OpenGLInit_impl(RendererData* apiData)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	return TRUE;
}

void OpenGLOnWindowResize_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 drawIndexCount)
{
	glViewport(x, y, width, height);
}

void OpenGLBeginRendering_impl(FE_Color * clearColor)
{
	glClearColor(clearColor->r, clearColor->g, clearColor->b, clearColor->a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDrawIndex_impl(Uint32 indexCount)
{
}

void OpenGLShutdown_impl()
{
}