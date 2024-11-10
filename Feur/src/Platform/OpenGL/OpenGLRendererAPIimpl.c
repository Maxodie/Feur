#include "fepch.h"
#include "Platform/OpenGL/OpenGLRendererAPIimpl.h"

#include <glad/glad.h>

Bool OpenGLInit_impl(RendererAPIData* apiData)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	return TRUE;
}

void OpenGLOnWindowResize_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
	glViewport(x, y, width, height);
}

void OpenGLBeginRendering_impl(ILDA_vector4f * clearColor)
{
	glClearColor(clearColor->x, clearColor->y, clearColor->z, clearColor->w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDrawIndex_impl()
{
}

void OpenGLShutdown_impl()
{
}