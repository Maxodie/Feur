#pragma once

typedef struct FE_ECSSystemContext
{
	FE_EntityRegistry* registry;
	Double dt;
} FE_ECSSystemContext;

void FE_ECSComputeCameraMovement(FE_CompCamera3D* cameraComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context);

void FE_ECSComputeAspectRatioUpdate(FE_CompCamera3D* cameraComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context);

void FE_ECSComputeDrawModel(FE_CompModel* modelComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context);

void FE_ECSComputeFreeModels(FE_CompModel* modelComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context);

void FE_ECSComputeSystem(void(fun)(void* comp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context), FE_EntityComponentTypeID compTypeId, FE_ECSSystemContext* context);