#include "Feur.h"

#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"

void UpdateSandboxLayerBase();
void OnRender(Layer* layer);
void UpdateLayerBaseEventSandbox(FE_Event* event);
void OnAttachSandboxLayerBase(Layer* layer);

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
const char* LoadFile(const char* filePath);
void emptyf() {}

Layer layer = { .OnUpdate = emptyf,.OnAttach = OnAttachSandboxLayerBase,.OnRender = OnRender, .OnUpdateLayerEvent = UpdateLayerBaseEventSandbox, .OnDetach = emptyf };

GLuint VertexArrayID; 
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

// This will identify our vertex buffer
GLuint vertexbuffer;
GLuint programID;

void StartSandbox()
{
	AddLayerApp(&layer);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	programID = LoadShaders("VertexShader.glsl", "FragmentShader.glsl");
}

void OnRender(Layer* layer)
{
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void UpdateSandboxLayerBase()
{
	
}


void UpdateLayerBaseEventSandbox(FE_Event* event)
{
}

void OnAttachSandboxLayerBase(Layer* layer)
{
	FE_LOG_DEBUG("Sandbox base layer attached");
}



GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	
	const char* VertexSourcePointer = LoadFile(vertex_file_path);

	// Read the Fragment Shader code from the file
	const char* FragmentSourcePointer = LoadFile(fragment_file_path);

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		GLchar* VertexShaderErrorMessage = malloc(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		GLchar* FragmentShaderErrorMessage = malloc(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		GLchar* ProgramErrorMessage = malloc(InfoLogLength);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

const char* LoadFile(const char* filePath)
{
	char* buffer = 0;
	long length;
	FILE* fptr = fopen(filePath, "rb");
	if (NULL == fptr)
	{
		FE_LOG_ERROR("ERROR::sandbox.c shader file named %s couldn't be loaded !", filePath);
		return NULL;
	}

	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr) + 1;
	fseek(fptr, 0, SEEK_SET);
	buffer = malloc(length);
	if (NULL != buffer)
	{
		fread(buffer, 1, length, fptr);
		buffer[length - 1] = '\0';
		fclose(fptr);
	}
	else
	{
		FE_LOG_ERROR("ERROR::sandbox.c file buffer of %s is NULL !", filePath);
	}
	
	fclose(fptr);
	return buffer;
}