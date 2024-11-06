#ifdef _FEUR_TEST_VULKAN_SANDBOX_
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

const char* LoadFile(const char* filePath);
void emptyf() {}

Layer layer = { .OnUpdate = emptyf,.OnAttach = OnAttachSandboxLayerBase,.OnRender = OnRender, .OnUpdateLayerEvent = UpdateLayerBaseEventSandbox, .OnDetach = emptyf };

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
	
//	==========================    FE_list test 
	/*FE_List(Uint32) test = { 0 };
	FE_ListInit(test);
	FE_ListEmplace(test, Uint32, 59);
	FE_ListEmplace(test, Uint32, 59);
	FE_ListEmplace(test, Uint32, 59);

	FE_LOG_DEBUG("test default");
	for (Uint32 i = 0; i < test.impl.count; i++)
	{
		FE_LOG_DEBUG("test : %d  :  %d", i, test.data[i]);
	}

	Uint32 temp = 78;
	FE_ListInsert(test, temp, 1);

	FE_LOG_DEBUG("test insert id : 1");
	for (Uint32 i = 0; i < test.impl.count; i++)
	{
		FE_LOG_DEBUG("test : %d  :  %d", i, test.data[i]);
	}

	FE_ListEmplace(test, Uint32, 45);
	FE_LOG_DEBUG("test push");
	for (Uint32 i = 0; i < test.impl.count; i++)
	{
		FE_LOG_DEBUG("test : %d  :  %d", i, test.data[i]);
	}

	FE_ListRemove(test, 2);

	FE_LOG_DEBUG("test remove id : 2");
	for (Uint32 i = 0; i < test.impl.count; i++)
	{
		FE_LOG_DEBUG("test : %d  :  %d", i, test.data[i]);
	}

	FE_ListRemoveDuplicate(test);
	FE_LOG_DEBUG("test remove duplication");
	for (Uint32 i = 0; i < test.impl.count; i++)
	{
		FE_LOG_DEBUG("test : %d  :  %d", i, test.data[i]);
	}*/
}

void OnAttachSandboxLayerBase(Layer* layer)
{
	FE_LOG_DEBUG("Sandbox base layer attached");
}

void UpdateSandboxLayerBase()
{
}

void OnRender(Layer* layer)
{
	
}




void UpdateLayerBaseEventSandbox(FE_Event* event)
{
}



GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

	return GL_TRUE;
}

const char* LoadFile(const char* filePath)
{
	/*char* buffer = 0;
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
	return buffer;*/
}

#endif