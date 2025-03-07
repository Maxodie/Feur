#include "Feur/Core/Log/Log.h"
#include "Feur/Nuklear/NuklearLayer.h"
#ifdef _FEUR_TEST_VULKAN_SANDBOX_
#include "Feur.h"

#include <Nuklear/nuklear.h>
#include <stdio.h>

void UpdateSandboxLayerBase(Double dt);
void OnNuklearRender(NuklearGUIInterface* interface, Layer* layer);
void UpdateLayerBaseEventSandbox(FE_Event* event);
void OnAttachSandboxLayerBase(Layer* layer);
void EndLayer();

void OverlayUpdateSandboxLayerBase(Double dt);
void OverlayOnNuklearRender(NuklearGUIInterface* interface, Layer* layer);
void OverlayUpdateLayerBaseEventSandbox(FE_Event* event);
void OverlayOnAttachSandboxLayerBase(Layer* layer);
void OverlayEndLayer();

//const char* LoadFile(const char* filePath);

Layer layer = { .OnUpdate = UpdateSandboxLayerBase,.OnAttach = OnAttachSandboxLayerBase,.OnNuklearRender = OnNuklearRender, .OnUpdateLayerEvent = UpdateLayerBaseEventSandbox, .OnDetach = EndLayer };
Layer overlayLayer = { .OnUpdate = OverlayUpdateSandboxLayerBase,.OnAttach = OverlayOnAttachSandboxLayerBase,.OnNuklearRender = OverlayOnNuklearRender, .OnUpdateLayerEvent = OverlayUpdateLayerBaseEventSandbox, .OnDetach = OverlayEndLayer };

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
FE_CompCamera3D* cam = NULL;
ILDA_vector3f camMovement = { .z = -1 };
ILDA_vector3f camMovementLeft = { .x = -1 };
ILDA_vector3f camRotateAxis = { .z = 1 };

FE_EntityID squar0 = -1;
FE_CompTransform3D* compTransform0 = NULL;

FE_EntityID squar1 = -1;
FE_CompTransform3D* compTransform1 = NULL;

FE_EntityID cube3D = -1;
FE_Model3D cube;
FE_CompTransform3D* cubeTransform = NULL;
FE_CompModel* cubeModelComponent = NULL;

void StartSandbox()
{
	AddLayerApp(&layer);
	AddOverlayLayerApp(&overlayLayer);

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


	camEntity = FE_EntityCreate(&GetApp()->ecsRegistry);
	cam = FE_EntityAttachComp(&GetApp()->ecsRegistry, camEntity, GetApp()->cam3DComp);

	ILDA_vector3f pos = { .z = -2 };
	ILDA_vector3f worldUp = { .y = 1 };
	FE_CameraInit(&cam->camera, &pos, &worldUp, GetApp()->windowData.w / (Float32)GetApp()->windowData.h, 45.f, 0.0f, 1.0f);

	squar0 = FE_EntityCreate(&GetApp()->ecsRegistry);
	compTransform0 = FE_EntityAttachComp(&GetApp()->ecsRegistry, squar0, GetApp()->tr3DComp);
	compTransform0->position.x = 0.5f;
	compTransform0->scale = (ILDA_vector3f){ .x = 2.1f, .y = 0.1f, .z = 1.0f };

	squar1 = FE_EntityCreate(&GetApp()->ecsRegistry);
	compTransform1 = FE_EntityAttachComp(&GetApp()->ecsRegistry, squar1, GetApp()->tr3DComp);
	compTransform1->position.x = -1.f;
	compTransform1->scale = (ILDA_vector3f){ .x = 1.1f, .y = 1.2f, .z = 1.0f };

	if (FE_ModelLoad("Models/cube.fbx", &cube))
	{
		cube3D = FE_EntityCreate(&GetApp()->ecsRegistry);
		cubeTransform = FE_EntityAttachComp(&GetApp()->ecsRegistry, cube3D, GetApp()->tr3DComp);
		cubeTransform->position.x = 0.f;
		cubeTransform->scale = (ILDA_vector3f){ .x = 1.0f, .y = 1.0f, .z = 1.0f };

		cubeModelComponent = FE_EntityAttachComp(&GetApp()->ecsRegistry, cube3D, GetApp()->modelComp);
		cubeModelComponent->model = cube;
	}
}

ILDA_vector3f pos = { .x = 0.0f, .y = 0.0f, .z = 0.f };
ILDA_vector2f size = { .x = 1.0f, .y = 1.5f };
FE_Color color = { .r = .5f, .g = 0.1f, .b = 1.0f, .a = 0.2f};

ILDA_vector3f pos2 = { .x = 0.5f, .y = 0.0f, .z = 0.f };
ILDA_vector2f size2 = { .x = 1.1f, .y = 0.1f };
FE_Color color2 = { .r = .2f, .g = 1.f, .b = 0.0f, .a = 1.0f };

ILDA_vector3f pos3 = { .x = -1.f, .y = 0.0f, .z = 0.f };
ILDA_vector2f size3 = { .x = 1.1f, .y = 1.2f };
FE_Color color3 = { .r = 10.5f, .g = 10.1f, .b = 10.8f, .a = 1.f };

SizeT totalVertexCount = 0;
SizeT totalIndexCount = 0;

Double currentUpdateDt;

void UpdateSandboxLayerBase(Double dt)
{
	currentUpdateDt = dt;

	FE_ECSComputeSystem(FE_ECSComputeCameraMovement, GetApp()->cam3DComp, &GetApp()->ecsContext);

	FE_Renderer2DBeginScene(&cam->camera);


	FE_Renderer2DDrawQuad(&pos, &size, &color2);

	totalVertexCount = FE_Renderer2DGetVertexCount();
	totalIndexCount = FE_Renderer2DGetIndexCount();

	FE_Renderer2DEndScene();

	// 3d renderer
	FE_Renderer3DBeginScene(&cam->camera);

	FE_ECSComputeSystem(FE_ECSComputeDrawModel, GetApp()->modelComp, &GetApp()->ecsContext);

	totalVertexCount += FE_Renderer3DGetVertexCount();
	totalIndexCount += FE_Renderer3DGetIndexCount();

	FE_Renderer3DEndScene();
}



char vertexShaderPathBuf[256] = { 0 };
char fragmentShaderPathBuf[256] = { 0 };
char modelpathBuf[256] = { 0 };

char vertexCountBuf[256] = { 0 };
char indicesCountBuf[256] = { 0 };
char bufferCountBuf[256] = { 0 };

char msBuf[256] = { 0 };

void UploadVertexShaderEditor()
{
	if (vertexShaderPathBuf[0] == '\0')
	{
		return;
	}

	FE_ShaderChangeRenderPipeline(vertexShaderPathBuf, NULL);
	FE_UpdateRenderPipeline();
}

void UploadFragmentShaderEditor()
{
	if (fragmentShaderPathBuf[0] == '\0')
	{
		return;
	}

	FE_ShaderChangeRenderPipeline(NULL, fragmentShaderPathBuf);
	FE_UpdateRenderPipeline();
}

void LoadNewModelTask()
{
	FE_ModelFree(&cube);
	if (FE_ModelLoad(modelpathBuf, &cube))
	{
		cubeModelComponent->model = cube;
	}
}

void OnNuklearRender(NuklearGUIInterface* interface, Layer* layer)
{

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
	FE_ECSComputeSystem(FE_ECSComputeFreeModels, GetApp()->modelComp, &GetApp()->ecsContext);
}



Uint32 inspectorOverlay = { 0 };
Uint32 profilerOverlay = { 0 };
Uint32 viewportOverlay = { 0 };
//Overlay
void OverlayUpdateSandboxLayerBase(Double dt)
{
	FE_GUIOverlay* viewport = FE_GUIQueryOverlayByID(&GetApp()->guiInterface, viewportOverlay);
	FE_FrameBuffer* fb = &GetApp()->frameBuffer;
	if ((Uint32)viewport->rect.size.x != fb->w || (Uint32)viewport->rect.size.y != fb->h ||
		(Uint32)viewport->rect.position.x != fb->posX || (Uint32)viewport->rect.position.y != fb->posY)
	{
		FE_FrameBufferResize(
			fb,
			(Uint32)viewport->rect.position.x, (Uint32)viewport->rect.position.y,
			(Uint32)viewport->rect.size.x, (Uint32)viewport->rect.size.y
		);
	}
}

void OverlayOnNuklearRender(NuklearGUIInterface* interface, Layer* layer)
{
	struct nk_context* context = (struct nk_context*)interface->handle;

	if (FE_OverlayGUIBegin(interface, profilerOverlay))
	{
		nk_layout_row_dynamic(context, 20, 1);

		//stats
		FE_StringFormat(bufferCountBuf, "ms : %f", currentUpdateDt);
		nk_label(context, bufferCountBuf, NK_TEXT_LEFT);

		FE_StringFormat(vertexCountBuf, "vertex count : %lld", totalVertexCount);
		nk_label(context, vertexCountBuf, NK_TEXT_LEFT);

		FE_StringFormat(indicesCountBuf, "index count : %lld", totalIndexCount);
		nk_label(context, indicesCountBuf, NK_TEXT_LEFT);

		FE_StringFormat(bufferCountBuf, "total vertex buffer count : %lld", FE_Renderer3DGetVertexBufferCount() + FE_Renderer2DGetVertexBufferCount());
		nk_label(context, bufferCountBuf, NK_TEXT_LEFT);
		//stats

		FE_OverlayGUIEnd(interface, profilerOverlay);
	}


	if (FE_OverlayGUIBegin(interface, inspectorOverlay))
	{
		nk_layout_row_dynamic(context, 20, 1);

		// in window
		nk_edit_string_zero_terminated(context, NK_EDIT_FIELD, vertexShaderPathBuf, sizeof(vertexShaderPathBuf) - 1, nk_filter_default);
		if (nk_button_label(context, "Submit vertex shaders"))
		{
			UploadVertexShaderEditor();
		}

		nk_edit_string_zero_terminated(context, NK_EDIT_FIELD, fragmentShaderPathBuf, sizeof(fragmentShaderPathBuf) - 1, nk_filter_default);
		if (nk_button_label(context, "Submit fragment shaders"))
		{
			UploadFragmentShaderEditor();
		}

		if (nk_button_label(context, "Update graphics pipeline"))
		{
			FE_UpdateRenderPipeline();
		}

		nk_edit_string_zero_terminated(context, NK_EDIT_FIELD, modelpathBuf, sizeof(modelpathBuf) - 1, nk_filter_default);
		if (nk_button_label(context, "Load new model (check the path nerd (project local))"))
		{
			FE_EventPostTask(&GetApp()->eventRegistry, LoadNewModelTask);
		}

		FE_PropertyGUITransformField(interface, cubeTransform);

		nk_layout_row_dynamic(context, 20, 1);
		nk_label(context, "background:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(context, 25, 1);
		struct nk_colorf background = { .r = color2.r, .g = color2.g, .b = color2.b, .a = color2.a };
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

		FE_OverlayGUIEnd(interface, inspectorOverlay);
	}

}

void OverlayUpdateLayerBaseEventSandbox(FE_Event* event)
{
}

void OverlayOnAttachSandboxLayerBase(Layer* layer)
{
	NuklearGUIInterface* api = &GetApp()->guiInterface;

    FE_CORE_LOG_DEBUG("Start dock 1");
	inspectorOverlay = FE_GUICreateOverlay(api, "#Nuklear Window");
	viewportOverlay = FE_GUICreateOverlay(api, "#viewport");
	profilerOverlay = FE_GUICreateOverlay(api, "#profiler");
    FE_CORE_LOG_DEBUG("Start dock 2");

    FE_DockGUIDockOverlay(api, viewportOverlay, 0, FE_OVERLAY_POSITION_LEFT);

    FE_GUIOverlay* overlay = FE_GUIQueryOverlayByID(api, inspectorOverlay);
    overlay->rect.size.x /= 4.f;
    FE_DockGUIDockOverlay(api, inspectorOverlay, 0, FE_OVERLAY_POSITION_RIGHT);

    overlay = FE_GUIQueryOverlayByID(api, profilerOverlay);
    overlay->rect.size.y /= 4.f;
    FE_DockGUIDockOverlay(api, profilerOverlay, 1, FE_OVERLAY_POSITION_BOTTOM);

    /*FE_DockGUIPrintCurrentState(api);*/
    /*FE_DockGUIUndockOverlay(api, profilerOverlay);*/
    /*FE_DockGUIPrintCurrentState(api);*/
}

void OverlayEndLayer()
{
	//FE_GridLayoutGUIRemoveOverlay(&GetApp()->guiInterface, &inspectorOverlay);
}

#endif
