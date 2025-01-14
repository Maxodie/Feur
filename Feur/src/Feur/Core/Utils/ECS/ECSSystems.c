#include "fepch.h"
#include "Feur/Core/Utils/ECS/ECSSystems.h"

void FE_ECSComputeDraw(FE_CompMesh* meshComp, FE_EntityComponentTypeID compTypeId, FE_EntityID entityId, FE_ECSSystemContext* context)
{
	FE_CompTransform3D* tr = FE_EntityComponentQueryFromID(context->registry, entityId, compTypeId);// exemple on how to get any component type of this entity
	tr->position.x += 0.1f * (Float32)context->dt;

}

void FE_ECSComputeSystem(void(fun)(void* comp, FE_EntityID entityId, FE_ECSSystemContext* context), FE_EntityComponentTypeID compTypeId, FE_ECSSystemContext* context) // maybe give a context data
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

		fun((void*)((UintptrT)comps + compList->compSize * i), entityIds[i], context);
	}
}