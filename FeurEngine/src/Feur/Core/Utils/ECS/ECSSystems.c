#include "fepch.h"
#include "Feur/Core/Utils/ECS/ECSSystems.h"
#include "Feur/Core/Input/Input.h"

void FE_ECSComputeCameraMovement(FE_CompCamera3D* cameraComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context)
{
	if (FE_IsInputPressed(FE_KEYCODE_W))
	{
		ILDA_vector3f move = (ILDA_vector3f){ 0.0f, 0.0f, 1.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);
	}

	if (FE_IsInputPressed(FE_KEYCODE_S))
	{
		ILDA_vector3f move = (ILDA_vector3f){ 0.0f, 0.0f, -1.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);
	}

	if (FE_IsInputPressed(FE_KEYCODE_A))
	{
		ILDA_vector3f move = (ILDA_vector3f){ -1.0f, 0.0f, 0.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);
	}
	if (FE_IsInputPressed(FE_KEYCODE_D))
	{
		ILDA_vector3f move = (ILDA_vector3f){ 1.0f, 0.0f, 0.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);

	/*	ILDA_vector3f rotationAxis = (ILDA_vector3f){ 0.0f, 0.0f, -1.0f };
		FE_CameraRotate(&cameraComp->camera, &rotationAxis, 2.f);*/
	}
	if (FE_IsInputPressed(FE_KEYCODE_Q))
	{
		ILDA_vector3f move = (ILDA_vector3f){ 0.0f, -1.0f, 0.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);
	}
	if (FE_IsInputPressed(FE_KEYCODE_E))
	{
		ILDA_vector3f move = (ILDA_vector3f){ 0.0f, 1.0f, 0.0f };
		ILDA_vector3f_mul(&move, (Float32)context->dt);
		FE_CameraMove(&cameraComp->camera, &move);
	}
}

void FE_ECSComputeAspectRatioUpdate(FE_CompCamera3D* cameraComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context)
{
	FE_CameraSetPerspective(&cameraComp->camera, GetApp()->frameBuffer.w / (Float32)GetApp()->frameBuffer.h, cameraComp->camera.fov, cameraComp->camera.zNear, cameraComp->camera.zFar);
}

void FE_ECSComputeDrawModel(FE_CompModel* modelComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context)
{
	FE_CompTransform3D* tr = FE_EntityComponentQueryFromID(context->registry, entityId, GetApp()->tr3DComp);
	//tr->position.x += 0.1f * (Float32)context->dt;

	FE_Renderer3DDrawModel(&modelComp->model, tr);
}

void FE_ECSComputeFreeModels(FE_CompModel* modelComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context)
{
	FE_ModelFree(&modelComp->model);
}

void FE_ECSComputeSystem(void(fun)(void* comp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context), FE_EntityComponentTypeID compTypeId, FE_ECSSystemContext* context) // maybe give a context data
{
	FE_EntityComponentList* compList = FE_EntityComponentListQueryFromID(context->registry, compTypeId);

	void* comps = compList->dataList;
	FE_EntityID* entityIds = context->registry->compEntityUuids.data[compTypeId].data;
	for (SizeT i = 0; i < compList->count; i++)
	{
		if (entityIds[i] == -1)
		{
			continue;
		}

		fun((void*)((UintptrT)comps + compList->compSize * i), compTypeId, entityIds[i], context);
	}
}