#include "fepch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

Bool FE_API OpenGLInit_impl(RendererAPIData* apiData)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	return TRUE;
}

void FE_API OpenGLSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
	glViewport(x, y, width, height);
}

void FE_API OpenGLClearScreenColor_impl()
{
	glClearColor(100, 0, 100, 255);
}

void FE_API OpenGLClear_impl()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FE_API OpenGLDrawIndex_impl()
{
}

void FE_API OpenGLShutdown_impl(RendererAPIData* apiData)
{
}