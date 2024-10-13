#ifdef _FEUR_TEST_OPENGL_SANDBOX_
#include "Feur.h"

#include "glad/glad.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ILDA_matrix/ILDA_matrix.h"
#include "ILDA_trigo/ILDA_trigo.h"

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

/*ILDA_matrix4x4 modelViewProjection = {.rowCount = 4, .colCount = 4, .data = {
		{1.086396f, -0.993682f, -0.687368f, -0.685994},
		{ 0.000000f, 2.070171f, -0.515526f, -0.514496},
		{ -1.448528f, -0.745262f, -0.515526f, -0.514496 },
		{ 0.000000f, 0.000000f, 5.642426f, 5.830953f }
} };*/
ILDA_matrix4x4 modelViewProjection;

void tempMatrixPrint(const ILDA_matrix4x4* matrix)
{
	int index;
	int jdex;
	for (index = 0; index < ILDA_matrix4x4_row; index++) {
		for (jdex = 0; jdex < ILDA_matrix4x4_col; jdex++) {
			printf("%f ", matrix->data[index][jdex]);
		}
		printf("\n");
	}
}


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


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ILDA_matrix4x4 projection = ILDA_matrix_perspective_r(ILDA_radians(45.f), (float)GetApp()->windowData.w / (float)GetApp()->windowData.h, 0.1f, 100.0f);
	//ILDA remove this and make it const global for all matrices + add trigo func like Radians

	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	ILDA_vector3f location = { .x = 4, .y = 3, .z = 3 };// Camera is at (4,3,3), in World Space
	ILDA_vector3f target = { .x = 0, .y = 0, .z = 0 };// and looks at the origin
	ILDA_vector3f worldUp = { .x = 0, .y = 1, .z = 0 };// Head is up (set to 0,-1,0 to look upside-down)
	ILDA_matrix4x4 view = ILDA_matrix_look_at_r(&location, &target, &worldUp);

	// Model matrix : an identity matrix (model will be at the origin)
	ILDA_matrix4x4 model = ILDA_matrix4x4_identity;
	// Our ModelViewProjection : multiplication of our 3 matrices
	//ILDA_matrix4x4_mul_same(&modelViewProjection, &view);
	ILDA_matrix4x4_mul_same_source(&modelViewProjection, &model, &view);
	tempMatrixPrint(&modelViewProjection);
	ILDA_matrix4x4_mul_same(&modelViewProjection, &projection);
}

void OnRender(Layer* layer)
{
	glUseProgram(programID);

	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &modelViewProjection.data[0][0]);

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
#endif