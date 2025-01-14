#pragma once

typedef struct FE_ECSSystemContext
{
	FE_EntityRegistry* registry;
	Double dt;
} FE_ECSSystemContext;

void FE_ECSComputeDraw(FE_CompMesh* meshComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context);

void FE_ECSComputeSystem(void(fun)(void* comp, FE_EntityID entityId, FE_ECSSystemContext* context), FE_EntityComponentTypeID compTypeId, FE_ECSSystemContext* context);