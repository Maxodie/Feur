#pragma once

typedef struct FE_CompMesh
{
	FE_Mesh mesh;
} FE_CompMesh;

typedef struct FE_CompTransform3D
{
	ILDA_vector3f position;
	ILDA_vector3f rotation;
	ILDA_vector3f scale;
} FE_CompTransform3D;

typedef struct FE_CompCamera3D
{
	FE_Camera3D camera;
} FE_CompCamera3D;

typedef Int64 FE_EntityID;
typedef Int64 FE_EntityComponentTypeID;
typedef Int64 FE_EntityComponentID;

typedef struct FE_Entity
{
	FE_EntityID entityUuid;
	FE_ByteFlag byteFlag;
} FE_Entity;

typedef struct FE_EntityComponentList
{
	const SizeT compSize;
	SizeT count;
	void* dataList;
} FE_EntityComponentList;

typedef struct FE_EntityRegistry
{
	FE_List(FE_Entity) entities;
	FE_List(FE_EntityComponentTypeID) compUuids;
	FE_List(FE_List(FE_EntityID)) compEntityUuids;
	FE_List(FE_EntityComponentList) dataList;
} FE_EntityRegistry;


void FE_DECL FE_EntityCreateRegistry(FE_EntityRegistry* registry);
void FE_DECL FE_EntityDestroyRegistry(FE_EntityRegistry* registry);
FE_EntityID FE_DECL FE_EntityCreate(FE_EntityRegistry* registry);
void FE_DECL FE_EntityDestroy(FE_EntityRegistry* registry, FE_EntityID uuid);
FE_EntityComponentTypeID FE_DECL FE_EntityCreateComponentType(FE_EntityRegistry* registry, SizeT compSize);
void FE_DECL FE_EntityDestroyComponentType(FE_EntityRegistry* registry, FE_EntityComponentTypeID componentUuid);
void* FE_DECL FE_EntityAttachComp(FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid);
void FE_DECL FE_EntityDetachComp(FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid);

FE_Entity* FE_DECL FE_EntityQueryFromID(const FE_EntityRegistry* registry, FE_EntityID uuid);
FE_EntityComponentList* FE_DECL FE_EntityComponentListQueryFromID(const FE_EntityRegistry* registry, FE_EntityComponentTypeID uuid);
void* FE_DECL FE_EntityComponentQueryFromID(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid);
FE_EntityComponentID FE_DECL FE_EntityComponentIDQueryFromID(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid);

Bool FE_DECL FE_EntityHasComponent(const FE_EntityRegistry* registry, FE_EntityID entityUuid, FE_EntityComponentTypeID componentUuid);
void FE_DECL FE_EntityPrintEntityCompFlags(const FE_EntityRegistry* registry, FE_EntityID entityUuid);