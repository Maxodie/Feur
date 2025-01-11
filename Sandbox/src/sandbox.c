#ifdef _FEUR_TEST_VULKAN_SANDBOX_
#include "Feur.h"

#include <Nuklear/nuklear.h>
#include <stdio.h>

void UpdateSandboxLayerBase(Double dt);
void OnNuklearRender(NuklearGUIInterface* interface, Layer* layer);
void UpdateLayerBaseEventSandbox(FE_Event* event);
void OnAttachSandboxLayerBase(Layer* layer);
void EndLayer();

//const char* LoadFile(const char* filePath);

Layer layer = { .OnUpdate = UpdateSandboxLayerBase,.OnAttach = OnAttachSandboxLayerBase,.OnNuklearRender = OnNuklearRender, .OnUpdateLayerEvent = UpdateLayerBaseEventSandbox, .OnDetach = EndLayer };

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

FE_EntityID camEntity = -1;
FE_EntityComponentTypeID cam3DComp = -1;
FE_EntityRegistry ecsRegistry = { 0 };
FE_CompCamera3D* cam = NULL;
ILDA_vector3f camMovement = { .z = -1 };
ILDA_vector3f camRotateAxis = { .z = 1 };

FE_EntityComponentTypeID camTransform3DCompID = -1;

FE_EntityID squar0 = -1;
FE_CompTransform3D* compTransform0 = NULL;

FE_EntityID squar1 = -1;
FE_CompTransform3D* compTransform1 = NULL;

void StartSandbox()
{
	AddLayerApp(&layer); 

	FE_EntityCreateRegistry(&ecsRegistry);
	camEntity = FE_EntityCreate(&ecsRegistry);
	cam3DComp = FE_EntityCreateComponentType(&ecsRegistry, sizeof(FE_CompCamera3D));
	cam = FE_EntityAttachComp(&ecsRegistry, camEntity, cam3DComp);
	
	ILDA_vector3f pos = { .z = 1 };
	ILDA_vector3f worldUp = { .y = 1 };
	FE_CameraInit(&cam->camera, &pos, &worldUp, GetApp()->windowData.w / (Float32)GetApp()->windowData.h, 45.f, 0.0f, 1.0f);

	camTransform3DCompID = FE_EntityCreateComponentType(&ecsRegistry, sizeof(FE_CompTransform3D));

	squar0 = FE_EntityCreate(&ecsRegistry);
	compTransform0 = FE_EntityAttachComp(&ecsRegistry, squar0, camTransform3DCompID);
	compTransform0->position.x = 0.5f;
	compTransform0->scale = (ILDA_vector3f){ .x = 1.1f, .y = 0.1f, .z = 1.0f };

	squar1 = FE_EntityCreate(&ecsRegistry);
	compTransform1 = FE_EntityAttachComp(&ecsRegistry, squar1, camTransform3DCompID);
	compTransform1->position.x = -1.f;
	compTransform1->scale = (ILDA_vector3f){ .x = 1.1f, .y = 1.2f, .z = 1.0f};

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

ILDA_vector3f pos = { .x = 0.0f, .y = 0.0f, .z = 0.f };
ILDA_vector2f size = { .x = 1.0f, .y = 1.5f };
FE_Color color = { .r = .5f, .g = 0.1f, .b = 1.0f, .a = 0.2f};

//ILDA_vector3f pos2 = { .x = 0.5f, .y = 0.0f, .z = 0.f }; pos2 = compTransform0
//ILDA_vector2f size2 = { .x = 1.1f, .y = 0.1f }; size2 = compTransform0
FE_Color color2 = { .r = .2f, .g = 1.f, .b = 0.0f, .a = 0.2f };

//ILDA_vector3f pos3 = { .x = -1.f, .y = 0.0f, .z = 0.f }; pos3 = compTransform1
//ILDA_vector2f size3 = { .x = 1.1f, .y = 1.2f }; size3 = compTransform0
FE_Color color3 = { .r = 10.5f, .g = 10.1f, .b = 10.8f, .a = 1.f };



void UpdateSandboxLayerBase(Double dt)
{
	FE_Renderer2DBeginScene(&cam->camera);

	if (FE_IsInputPressed(FE_KEYCODE_W))
	{
		FE_Renderer2DDrawQuad(&pos, &size, &color); 
		ILDA_vector3f move = camMovement;
		ILDA_vector3f_mul(&move, (Float32)dt);
		FE_CameraMove(&cam->camera, &move);
	}

	if (FE_IsInputPressed(FE_KEYCODE_S))
	{
		FE_Renderer2DDrawQuad(&pos, &size, &color);
		ILDA_vector3f move = camMovement;
		ILDA_vector3f_mul(&move, (Float32) - dt);
		FE_CameraMove(&cam->camera, &move);
	}

	if (FE_IsInputPressed(FE_KEYCODE_A))
	{
		FE_Renderer2DDrawQuad(&pos, &size, &color);
		//pos2.x -= (float)dt * 10;
		//FE_CameraMove(&cam, &camMovement);
		FE_CameraRotate(&cam->camera, &camRotateAxis, 2.f);
	}
	if (FE_IsInputPressed(FE_KEYCODE_D))
	{
		FE_Renderer2DDrawQuad(&pos, &size, &color);
		//pos2.x -= (float)dt * 10;
		//FE_CameraMove(&cam, &camMovement);
		FE_CameraRotate(&cam->camera, &camRotateAxis, -2.f);
	}

	FE_EntityComponentList* tr3DcompList = FE_EntityComponentListQueryFromID(&ecsRegistry, camTransform3DCompID);
	FE_CompTransform3D* transform3Ds = tr3DcompList->dataList.data;
	FE_EntityID* entityIds = ecsRegistry.compEntityUuids.data[camTransform3DCompID].data;
	for (SizeT i = 0; i < tr3DcompList->dataList.impl.count; i++)
	{
		FE_CompTransform3D* tr = FE_EntityComponentQueryFromID(&ecsRegistry, entityIds[i], camTransform3DCompID);// exemple on how to get any component type of this entity
		tr->position.x += 0.1f * dt;

		FE_Renderer2DDrawQuad(&transform3Ds[i].position, &transform3Ds[i].scale, &color2);
	}

	FE_Renderer2DEndScene();
}

void OnNuklearRender(NuklearGUIInterface* interface, Layer* layer)
{
	struct nk_context* context = (struct nk_context*)interface->handle;
	if (nk_begin(context, "Nuklear Window", nk_rect(0, 0, 500, 500), NK_WINDOW_TITLE | NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE))
	{
		struct nk_vec2 rect = nk_window_get_content_region_min(context);
		struct nk_vec2 size = nk_window_get_content_region_size(context);

		struct nk_vec2 tabPos = nk_window_get_content_region_max(context);
		struct nk_vec2 winSize = { .x = (Float32)GetApp()->windowData.w, .y = (Float32)GetApp()->windowData.h };

		struct nk_colorf background = { .r = color2.r, .g = color2.g, .b = color2.b, .a = color2.a };
		nk_layout_row_static(context, 30, 80, 1);
		if (nk_button_label(context, "button"))
			fprintf(stdout, "button pressed\n");

		nk_layout_row_dynamic(context, 20, 1);
		nk_label(context, "background:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(context, 25, 1);
		if (nk_combo_begin_color(context, nk_rgb_cf(background),
			nk_vec2(nk_widget_width(context), 400))) {
			nk_layout_row_dynamic(context, 120, 1);
			background = nk_color_picker(context, background, NK_RGBA);
			color2.r = background.r;
			color2.g = background.g;
			color2.b = background.b;
			color2.a = background.a;
			nk_layout_row_dynamic(context, 25, 1);
			nk_combo_end(context);
		}

		//FE_CORE_LOG_DEBUG("x : %f; y : %f", rect.x, rect.y);
	}
	nk_end(context);
}




void UpdateLayerBaseEventSandbox(FE_Event* event)
{
}
//const char* LoadFile(const char* filePath)
//{
//	/*char* buffer = 0;
//	long length;
//	FILE* fptr = fopen(filePath, "rb");
//	if (NULL == fptr)
//	{
//		FE_LOG_ERROR("ERROR::sandbox.c shader file named %s couldn't be loaded !", filePath);
//		return NULL;
//	}
//
//	fseek(fptr, 0, SEEK_END);
//	length = ftell(fptr) + 1;
//	fseek(fptr, 0, SEEK_SET);
//	buffer = malloc(length);
//	if (NULL != buffer)
//	{
//		fread(buffer, 1, length, fptr);
//		buffer[length - 1] = '\0';
//		fclose(fptr);
//	}
//	else
//	{
//		FE_LOG_ERROR("ERROR::sandbox.c file buffer of %s is NULL !", filePath);
//	}
//	
//	fclose(fptr);
//	return buffer;*/
//}

void EndLayer() 
{
	FE_EntityDestroyRegistry(&ecsRegistry);
}

#endif