#include "fepch.h"
#include "Feur/Core/Utils/ECS/ECS.h"

void FE_EntityCreateRegistry(FE_EntityRegistry* registry)
{
	FE_ListInit(registry->entities);
	FE_ListInit(registry->compUuids);
	FE_ListInit(registry->dataList);
	FE_ListInit(registry->compEntityUuids);
}

void FE_EntityDestroyRegistry(FE_EntityRegistry* registry)
{
	SizeT count = registry->entities.impl.count;
	for (SizeT i = 0; i < count; i++)
	{
		FE_FlagDestroy(&registry->entities.data[i].byteFlag);
	}

	FE_ListClear(registry->entities);
	FE_ListClear(registry->compUuids);

	count = registry->dataList.impl.count;
	for (SizeT i = 0; i < count; i++)
	{
		FE_MemoryGeneralFree(registry->dataList.data[i].dataList);
		FE_ListClear(registry->compEntityUuids.data[i]);
	}

	FE_ListClear(registry->compEntityUuids);
	FE_ListClear(registry->dataList);
	
}

FE_EntityID FE_EntityCreate(FE_EntityRegistry* registry)
{
	FE_EntityID entityId = -1;

	for (SizeT i = 0; i < registry->entities.impl.count; i++)
	{
		if (registry->entities.data[i].entityUuid == -1)
		{
			entityId = i;
			registry->entities.data[i].entityUuid = i;

			FE_FlagReset(&registry->entities.data[i].byteFlag);
			return entityId;
		}
	}

	entityId = registry->entities.impl.count;

	FE_ListPush(registry->entities, entityId);
	FE_FlagInit(&registry->entities.data[entityId].byteFlag);

	return entityId;
}

void FE_EntityDestroy(FE_EntityRegistry* registry, FE_EntityID uuid)
{
	FE_Entity* entity = FE_EntityQueryFromID(registry, uuid);

	FE_EntityComponentID singleCompID = -1;
	FE_EntityComponentTypeID* compTypeUuids = registry->compUuids.data;

	for (SizeT i = 0; i < registry->compUuids.impl.count; i++)
	{
		if(FE_FlagExist(&entity->byteFlag, compTypeUuids[i]))
		{
			singleCompID = FE_EntityComponentIDQueryFromID(registry, uuid, i);
			registry->compEntityUuids.data[compTypeUuids[i]].data[singleCompID] = -1;
		}
	}

	FE_FlagReset(&entity->byteFlag);
	entity->entityUuid = -1;
}

FE_EntityComponentTypeID FE_EntityCreateComponentType(FE_EntityRegistry* registry, SizeT compSize)
{
	FE_EntityComponentTypeID uuid = -1;

	for (SizeT i = 0; i < registry->dataList.impl.count; i++)
	{
		if (registry->compUuids.data[i] == -1)
		{
			uuid = i;
			registry->compUuids.data[i] = uuid;
			return uuid;
		}
	}

	uuid = registry->compUuids.impl.count;

	FE_ListPush(registry->compUuids, uuid);

	FE_EntityComponentList compList = { .compSize = compSize };
	FE_List(FE_EntityID) entityUuids = { 0 };
	FE_ListInit(entityUuids);

	FE_ListPush(registry->compEntityUuids, entityUuids);
	FE_ListPush(registry->dataList, compList);

	return uuid;
}

void FE_EntityDestroyComponentType(FE_EntityRegistry* registry, FE_EntityComponentTypeID componentUuid)
{
	FE_Entity* entities = registry->entities.data;
	SizeT entityCount = registry->entities.impl.count;
	for (SizeT i = 0; i < entityCount; i++)
	{
		FE_FlagRemove(&entities[i].byteFlag, componentUuid);
	}

	FE_MemoryGeneralFree(registry->dataList.data[componentUuid].dataList);
	FE_ListClear(registry->compEntityUuids.data[componentUuid]);
	registry->compUuids.data[componentUuid] = -1;
}

void* FE_EntityAttachComp(FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid)
{
	FE_Entity* entity = FE_EntityQueryFromID(registry, entityUuid);

	if (FE_FlagExist(&entity->byteFlag, componentUuid))
	{
		return NULL;
	}

	FE_EntityComponentList* compList = FE_EntityComponentListQueryFromID(registry, componentUuid);

	FE_EntityID* compEntities = registry->compEntityUuids.data[componentUuid].data;
	SizeT compEntitiesCount = registry->compEntityUuids.data[componentUuid].impl.count;
	SizeT uuid = -1;

	for (SizeT i = 0; i < compEntitiesCount; i++)
	{
		if (compEntities[i] == -1)
		{
			uuid = i;
			compEntities[i] = uuid;
			void* existingComp = (void*)((UintptrT)compList->dataList + ((UintptrT)compList->compSize * i));
			memset(existingComp, 0, compList->compSize);
			FE_FlagSet(&entity->byteFlag, componentUuid);
			return existingComp;
		}
	}

	if (compList->dataList == NULL)
	{
		compList->dataList = FE_MemoryGeneralAlloc(compList->compSize);
		compList->count++;
	}
	else
	{
		compList->dataList = FE_MemoryGeneralRealloc(compList->dataList, (compList->count++ + 1) * compList->compSize);
	}

	void* newComp = (void*)((UintptrT)compList->dataList + (compList->compSize * (compList->count - 1)));

	memset(newComp, 0, compList->compSize);
	FE_FlagSet(&entity->byteFlag, componentUuid);

	FE_ListPush(registry->compEntityUuids.data[componentUuid], entityUuid);

	return newComp;
}

void FE_EntityDetachComp(FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid)
{
	FE_Entity* entity = FE_EntityQueryFromID(registry, entityUuid);

	if (!FE_FlagExist(&entity->byteFlag, componentUuid))
	{
		return;
	}

	FE_EntityComponentList* compList = FE_EntityComponentListQueryFromID(registry, componentUuid);
	
	FE_EntityComponentID singleCompUuid = FE_EntityComponentIDQueryFromID(registry, entityUuid, componentUuid);

	registry->compEntityUuids.data[componentUuid].data[singleCompUuid] = -1;
	
	FE_FlagRemove(&entity->byteFlag, componentUuid);

}

FE_Entity* FE_EntityQueryFromID(const FE_EntityRegistry* registry, FE_EntityID uuid)
{
	if ((Int64)registry->entities.impl.count <= uuid || registry->entities.data[uuid].entityUuid != uuid)
	{
		FE_CORE_ASSERT(FALSE, "The FE_Entity is invalid");
		return NULL;
	}

	return registry->entities.data + uuid;

}

FE_EntityComponentList* FE_EntityComponentListQueryFromID(const FE_EntityRegistry* registry, FE_EntityComponentTypeID uuid)
{
	if ((Int64)registry->dataList.impl.count <= uuid || (Int64)registry->compUuids.impl.count <= uuid || registry->compUuids.data[uuid] != uuid)
	{
		FE_CORE_ASSERT(FALSE, "The FE_EntityComponentTypeID is invalid");
		return NULL;
	}

	return registry->dataList.data + uuid;
}

void* FE_EntityComponentQueryFromID(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid)
{
	if ((Int64)registry->dataList.impl.count <= componentUuid || registry->compUuids.data[componentUuid] != componentUuid)
	{
		FE_CORE_ASSERT(FALSE, "The FE_EntityComponentTypeID is invalid");
		return NULL;
	}

	FE_EntityComponentID singleCompUuid = FE_EntityComponentIDQueryFromID(registry, entityUuid, componentUuid);

	if (singleCompUuid == -1)
	{
		FE_CORE_ASSERT(FALSE, "The FE_EntityComponentID is invalid");
		return NULL;
	}

	return (void*)((UintptrT)(registry->dataList.data[componentUuid].dataList) + singleCompUuid * registry->dataList.data[componentUuid].compSize);
}

FE_EntityComponentID FE_EntityComponentIDQueryFromID(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid)
{
	if ((Int64)registry->compEntityUuids.impl.count <= componentUuid)
	{
		FE_CORE_ASSERT(FALSE, "The FE_EntityComponentTypeID is invalid");
		return -1;
	}

	FE_EntityID* uuids = registry->compEntityUuids.data[componentUuid].data;
	SizeT count = registry->compEntityUuids.data[componentUuid].impl.count;
	for (SizeT i = 0; i < count; i++)
	{
		if (uuids[i] == entityUuid)
		{
			return i;
		}
	}

	return -1;
}

Bool FE_EntityHasComponent(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid)
{
	FE_Entity* entity = FE_EntityQueryFromID(registry, entityUuid);

	return FE_FlagExist(&entity->byteFlag, componentUuid);
}

void FE_EntityPrintEntityCompFlags(const FE_EntityRegistry* registry, FE_EntityID entityUuid)
{
	FE_Entity* entity = FE_EntityQueryFromID(registry, entityUuid);

	FE_FlagPrint(&entity->byteFlag);
}
