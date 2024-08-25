#include "fepch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLGraphicsContext.h"

#include <GLFW/glfw3.h>

void OpenGLG_GLFWraphicsContextInit(WindowData* windowData)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwMakeContextCurrent((GLFWwindow*)windowData->nativeWindow);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	FE_CORE_ASSERT(status, "Failed to initialize Glad !");
	
	FE_CORE_LOG_SUCCESS("   Vendor: %s", (const char*)glGetString(GL_VENDOR));
	FE_CORE_LOG_SUCCESS("   Renderer: %s", (const char*)glGetString(GL_RENDERER));
	FE_CORE_LOG_SUCCESS("   Version: %s", (const char*)glGetString(GL_VERSION));
}

void OpenGL_GLFWGraphicsContextSwapBuffers(WindowData* windowData)
{
	glfwSwapBuffers((GLFWwindow*)windowData->nativeWindow);
}
