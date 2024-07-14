#include "fepch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

BOOL OpenGLInit_Impl()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	return TRUE;
}

void OpenGLSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height)
{
	glViewport(x, y, width, height);
}

void OpenGLClearScreenColor_impl()
{
	glClearColor(100, 0, 100, 255);
}

void OpenGLClear_impl()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLDrawIndex_impl()
{
}
