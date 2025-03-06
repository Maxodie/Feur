#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include <Nuklear/nuklear.h>
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"
#include "Feur/Core/Input/Input.h"

void FE_DockGUIRecursionInvalidateDock(NuklearGUIInterface* api, FE_GUIDock* dock);
void FE_DockGUIDestroyCheckChildrenRecusrion(NuklearGUIInterface* api, FE_GUIDock* dock);

void NuklearGUIInterfaceInit(NuklearGUIInterface* api)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	api->overlayGUIMaxID = 0;
	FE_DockGUIInit(api);
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_OPENGL)
	{
		api->Init = OpenGL_GLFW_NuklearGUIInit_impl;
		api->Shutdown = OpenGL_GLFW_NuklearGUIShutdown_impl;
		api->OnEvent = OpenGL_GLFW_NuklearGUIEvent_impl;
		api->OnEndRender = OpenGL_GLFW_NuklearGUIEndRender_impl;
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_VULKAN)
	{
		api->Init = Vulkan_GLFW_NuklearGUIInit_impl;
		api->Shutdown = Vulkan_GLFW_NuklearGUIShutdown_impl;
		api->OnEvent = Vulkan_GLFW_NuklearGUIEvent_impl;
		api->OnBeginRender = Vulkan_GLFW_NuklearGUIBeginRender_impl;
		api->OnEndRender = Vulkan_GLFW_NuklearGUIEndRender_impl;
		api->OnWindowResize = Vulkan_GLFW_NuklearGUIOnWindowResize_impl;
	}
}

void NuklearGUIInterfaceShutdown(NuklearGUIInterface* api)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_DockGUIShutdown(api);
}

void NuklearGUIBeginRender()
{
	GetApp()->guiInterface.OnBeginRender(&GetApp()->guiInterface);
}

void NuklearGUIEndRender()
{
	GetApp()->guiInterface.OnEndRender();
}

Bool NuklearGUIInputLayerCheck(const NuklearGUIInterface* api)
{
    struct nk_context* context = (struct nk_context*)api->handle;
    if (context == NULL) return FALSE;
    return (context->last_widget_state & NK_WIDGET_STATE_MODIFIED);
}

void FE_DECL NuklearGUIOnWindowResize(const NuklearGUIInterface* api, Uint32 width, Uint32 height)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	api->OnWindowResize(width, height);

    FE_GUIDock* dock = FE_ListGet(api->guiDockLayout.docks, 0);
    FE_DockGUIChangeScale(api, dock, 0, 0, width, height);
	FE_DockGUIRecursionInvalidateDock(api, FE_ListGet(api->guiDockLayout.docks, 0));
}

void FE_DockGUIPrintDockInfos(const NuklearGUIInterface* api, const FE_GUIDock* dock)
{
	FE_CORE_ASSERT(dock != NULL, "FE_GUIDock dock is NULL");
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_CORE_LOG_DEBUG("Dock Infos ======================================================");
	FE_CORE_LOG_DEBUG("Dock IsDestroyed : %s", dock->isDestroyed ? "true" : "false");
	FE_CORE_LOG_DEBUG("Dock id: %d", dock->id);
	FE_CORE_LOG_DEBUG("Dock rect: x: %f   y: %f   width: %f   height: %f", dock->rect.position.x, dock->rect.position.y, dock->rect.size.x, dock->rect.size.y);
	if (dock->linkedOverlayId >= 0)
	{
		FE_CORE_LOG_DEBUG("Dock linked overlay: %p      name: %s", &api->guiDockLayout.overlays.data[dock->linkedOverlayId], api->guiDockLayout.overlays.data[dock->linkedOverlayId].name);
	}
	else
	{
		FE_CORE_LOG_DEBUG("Dock linked overlay: %d", dock->linkedOverlayId);
	}
	FE_CORE_LOG_DEBUG("Dock type: %d", dock->type);

	for (SizeT i = 0; i < dock->childrenDockId.impl.count; i++)
	{
		FE_CORE_LOG_DEBUG("Dock child: id order: %d   child id: %d", dock->type, dock->childrenDockId.data[i]);
	}
}

void FE_DockGUIPrintCurrentState(NuklearGUIInterface* api)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_CORE_LOG_SUCCESS("Start Dock Infos (api list order) ---");
	for (SizeT i = 0; i < api->guiDockLayout.docks.impl.count; i++)
	{
		FE_DockGUIPrintDockInfos(api, &api->guiDockLayout.docks.data[i]);
	}
}

FE_GUIDock* FE_GUIQueryDockByID(NuklearGUIInterface* api, SizeT dockId)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
    FE_GUIDock* dock = FE_ListGet(api->guiDockLayout.docks, dockId);
    FE_CORE_ASSERT(dock != NULL, "requested overlay does not exist");
    return dock;
}

void FE_DockGUIInit(NuklearGUIInterface* api)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_ListInit(api->guiDockLayout.overlays);
	FE_ListInit(api->guiDockLayout.docks);

	FE_GUIRect rect = { .position = {.x = 0, .y = 0}, .size = {.x = GetApp()->windowData.w, .y = GetApp()->windowData.h} };
	FE_DockGUICreate(api, FE_GUI_DOCK_UNKNOWN, &rect);

	//api->baseOverlay = FE_GUICreateOverlay(api, "#defaultDockLayoutBase");
}

void FE_DockGUIShutdown(NuklearGUIInterface* api)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	for (SizeT i = 0; i < api->guiDockLayout.docks.impl.count; i++)
	{
		FE_ListClear(api->guiDockLayout.docks.data[i].childrenDockId);
	}

	FE_ListClear(api->guiDockLayout.docks);

	FE_ListClear(api->guiDockLayout.overlays);
}

SizeT FE_DockGUICreate(NuklearGUIInterface* api, FE_GUIDockType dockType, const FE_GUIRect* rect)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(rect != NULL, "FE_GUIRect rect is NULL");

	for (SizeT i = 0; i < api->guiDockLayout.docks.impl.count; i++)
	{
		if (api->guiDockLayout.docks.data[i].isDestroyed)
		{
			api->guiDockLayout.docks.data[i].isDestroyed = FALSE;
			api->guiDockLayout.docks.data[i].linkedOverlayId = -1,
            api->guiDockLayout.docks.data[i].rect = *rect;
			api->guiDockLayout.docks.data[i].type = dockType;
			api->guiDockLayout.docks.data[i].id = i;
			api->guiDockLayout.docks.data[i].parentID = -1;
			return i;
		}
	}

	FE_GUIDock rootDock = {
		.isDestroyed = FALSE,
		.linkedOverlayId = -1,
		.rect = *rect,
		.type = dockType,
		.id = api->guiDockLayout.docks.impl.count,
		.parentID = -1,
    };

	FE_ListInit(rootDock.childrenDockId);
	FE_ListPush(api->guiDockLayout.docks, rootDock);
	return rootDock.id;
}

SizeT FE_DockGUISlice(NuklearGUIInterface* api, SizeT dockId, FE_GUIOverlayPositions position, Float32 sliceProportion)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_GUIRect newSliceRect = { 0 };
	SizeT childrenCount = 0;
	SizeT slicedDockId = -1;

	Uint32 linkedOverlayNewPosition = 0;
	FE_GUIDock* tempDock = NULL;

	sliceProportion = ILDA_clamp(sliceProportion, 0.1f, 0.5f);

	switch (FE_GUIQueryDockByID(api, dockId)->type)
	{
	case FE_GUI_DOCK_VERTICAL:
		FE_CORE_ASSERT(position == FE_OVERLAY_POSITION_TOP || position == FE_OVERLAY_POSITION_BOTTOM, "given overlay position is incompatible with the dock type");
		childrenCount = FE_GUIQueryDockByID(api, dockId)->childrenDockId.impl.count;
		newSliceRect = FE_GUIQueryDockByID(api, dockId)->rect;

		if (!childrenCount)
		{
			FE_GUIRect defaultRect = { { 0, 0}, { FE_GUIQueryDockByID(api, dockId)->rect.size.x, FE_GUIQueryDockByID(api, dockId)->rect.size.y * (1 - sliceProportion)} };
			Int32 firstContent = FE_DockGUICreate(api, FE_GUI_DOCK_UNKNOWN, &defaultRect);
            FE_GUIDock* firstContentDock = FE_GUIQueryDockByID(api, firstContent);
			firstContentDock->linkedOverlayId = FE_GUIQueryDockByID(api, dockId)->linkedOverlayId;
            firstContentDock->parentID = dockId;
			FE_GUIQueryDockByID(api, dockId)->linkedOverlayId = -1;
			FE_ListPush(FE_GUIQueryDockByID(api, dockId)->childrenDockId, firstContent);
			childrenCount++;
		}

		newSliceRect.size.y = FE_GUIQueryDockByID(api, dockId)->rect.size.y * sliceProportion;

		if (childrenCount > 0 && position == FE_OVERLAY_POSITION_BOTTOM)
		{
			tempDock = FE_GUIQueryDockByID(api, FE_GUIQueryDockByID(api, dockId)->childrenDockId.data[childrenCount - 1]);
			newSliceRect.position.y = tempDock->rect.size.y + tempDock->rect.position.y;
		}

		slicedDockId = FE_DockGUICreate(api, FE_GUI_DOCK_UNKNOWN, &newSliceRect);

		if (position == FE_OVERLAY_POSITION_TOP)
		{
			linkedOverlayNewPosition = 1;
		}

		break;
	case FE_GUI_DOCK_HORIZONTAL:
		FE_CORE_ASSERT(position == FE_OVERLAY_POSITION_LEFT || position == FE_OVERLAY_POSITION_RIGHT, "given overlay position is incompatible with the dock type");
		childrenCount = FE_GUIQueryDockByID(api, dockId)->childrenDockId.impl.count;
		newSliceRect = FE_GUIQueryDockByID(api, dockId)->rect;

		if (!childrenCount)
		{
			FE_GUIRect defaultRect = { { 0, 0}, { FE_GUIQueryDockByID(api, dockId)->rect.size.x * (1 - sliceProportion), FE_GUIQueryDockByID(api, dockId)->rect.size.y} };
			Int32 firstContent = FE_DockGUICreate(api, FE_GUI_DOCK_UNKNOWN, &defaultRect);
            FE_GUIDock* firstContentDock = FE_GUIQueryDockByID(api, firstContent);
			firstContentDock->linkedOverlayId = FE_GUIQueryDockByID(api, dockId)->linkedOverlayId;
            firstContentDock->parentID = dockId;
			FE_GUIQueryDockByID(api, dockId)->linkedOverlayId = -1;
			FE_ListPush(FE_GUIQueryDockByID(api, dockId)->childrenDockId, firstContent);
			childrenCount++;
		}

		newSliceRect.size.x *= sliceProportion;

		if (childrenCount > 0 && position == FE_OVERLAY_POSITION_RIGHT)
		{
			tempDock = FE_GUIQueryDockByID(api, FE_GUIQueryDockByID(api, dockId)->childrenDockId.data[childrenCount - 1]);
			newSliceRect.position.x = tempDock->rect.size.x + tempDock->rect.position.x;
		}

		slicedDockId = FE_DockGUICreate(api, FE_GUI_DOCK_UNKNOWN, &newSliceRect);
		if (position == FE_OVERLAY_POSITION_LEFT)
		{
			linkedOverlayNewPosition = 1;
		}

		break;
	case FE_GUI_DOCK_UNKNOWN:
		FE_CORE_ASSERT(FALSE, "unknown given dock type");
		break;
	default:
		FE_CORE_ASSERT(FALSE, "unknown given dock type");
		break;
	}

    if(linkedOverlayNewPosition == 1)
    {
        FE_ListInsert(FE_GUIQueryDockByID(api, dockId)->childrenDockId, slicedDockId, 0);
    }
    else
    {
        FE_ListPush(FE_GUIQueryDockByID(api, dockId)->childrenDockId, slicedDockId);
    }

    FE_GUIQueryDockByID(api, slicedDockId)->parentID = dockId;

	FE_DockGUIRecursionInvalidateDock(api, FE_GUIQueryDockByID(api, dockId));

	return slicedDockId;
}

void FE_DockGUIDestroy(NuklearGUIInterface* api, SizeT dockId)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	api->guiDockLayout.docks.data[dockId].isDestroyed = TRUE;
    FE_GUIDock* currentDock = NULL;

    for(SizeT i = 0; i < api->guiDockLayout.docks.impl.count; i++)
    {
        currentDock = FE_ListGet(api->guiDockLayout.docks, i);
        for(SizeT y = 0; y < currentDock->childrenDockId.impl.count; y++)
        {
            if (api->guiDockLayout.docks.data[currentDock->childrenDockId.data[y]].isDestroyed)
            {
                FE_ListRemove(currentDock->childrenDockId, currentDock->childrenDockId.data[y]);
            }
        }
    }
}

Uint32 FE_GUICreateOverlay(NuklearGUIInterface* api, const char* name)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(name != NULL, "const char* name is NULL");

	FE_GUIOverlay newOverlay = {
		.flags = FE_OVERLAY_TITLE | FE_OVERLAY_BORDER,
		.name = name,
		.rect = (FE_GUIRect){ { 0, 0 }, { GetApp()->windowData.w, GetApp()->windowData.h }},
		.id = api->overlayGUIMaxID++,
		.isVisible = TRUE,
		.isDestroyed = FALSE,
	};

	FE_ListPush(api->guiDockLayout.overlays, newOverlay);

	return api->overlayGUIMaxID - 1;
}

void FE_DockGUIDestroyOverlay(NuklearGUIInterface* api, FE_GUIOverlay* overlayToRemove)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	overlayToRemove->isDestroyed = TRUE;
}

Float32 FE_DockGUIInvalidateOverflowCoefCalculation(SizeT childID, Float32 lastRectSize, Float32 lastRectPosition, Float32 dockRectPosition, Float32 dockRectSize, SizeT dockChildrenCount)
{
    Float32 result = (lastRectSize + lastRectPosition - dockRectPosition - dockRectSize) / dockRectSize / (Float32)dockChildrenCount;
    result = (Int32)(result * 1000.f - childID * .5f);
    return result / 1000.f;
}

void FE_DockGUIInvalidateDockOneDimention(NuklearGUIInterface* api, FE_GUIDock* dock, FE_GUIDock* childDock, Bool isVertical, FE_GUIRect* rect, Float32 overflowCoef, Float32* currentPos)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(dock != NULL, "Given dock is NULL");
	FE_CORE_ASSERT(dock->isDestroyed == FALSE, "Given dock has been destroyed");
	FE_CORE_ASSERT(childDock != NULL, "Given childDock is NULL");
	FE_CORE_ASSERT(childDock->isDestroyed == FALSE, "Given childDock has been destroyed");
	FE_CORE_ASSERT(currentPos != NULL, "Given currentPos is NULL");

    Float32 coef;

    if(isVertical)
    {
        coef = childDock->rect.size.y / dock->lastRect.size.y - overflowCoef;
        coef = ILDA_clamp(coef, 0.1f, 0.9f);

        childDock->rect.position.y = dock->rect.position.y + *currentPos;
        childDock->rect.size.y = dock->rect.size.y * coef;
        *currentPos += childDock->rect.size.y;

        childDock->rect.position.x = dock->rect.position.x;
        childDock->rect.size.x = dock->rect.size.x;
    }
    else
    {
        coef = childDock->rect.size.x / dock->lastRect.size.x - overflowCoef;
        coef = ILDA_clamp(coef, 0.1f, 0.9f);

        childDock->rect.position.x = dock->rect.position.x + *currentPos;
        childDock->rect.size.x = dock->rect.size.x * coef;
        *currentPos += childDock->rect.size.x;

        childDock->rect.position.y = dock->rect.position.y;
        childDock->rect.size.y = dock->rect.size.y;
    }

    if (childDock->linkedOverlayId >= 0)
    {
        FE_GUIQueryOverlayByID(api, childDock->linkedOverlayId)->rect = childDock->rect;
    }
}

void FE_DockGUIInvalidateDockRect(NuklearGUIInterface* api, FE_GUIDock* dock)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(dock->isDestroyed == FALSE, "Given dock has been destroyed");

	FE_GUIDock* childDock = NULL;
    switch (dock->type)
	{
	case FE_GUI_DOCK_VERTICAL:
        if(dock->childrenDockId.impl.count > 0)
        {
            FE_GUIRect* rect = &FE_GUIQueryDockByID(api, dock->childrenDockId.data[dock->childrenDockId.impl.count - 1])->rect;
            Float32 overflowCoef;
            FE_GUIDock* childDock = NULL;
            Float32 currentPos = 0;
            for (SizeT i = 0; i < dock->childrenDockId.impl.count; i++)
            {
                overflowCoef = FE_DockGUIInvalidateOverflowCoefCalculation(i, rect->size.y, rect->position.y, dock->lastRect.position.y, dock->lastRect.size.y, dock->childrenDockId.impl.count);

                childDock = FE_GUIQueryDockByID(api, dock->childrenDockId.data[i]);
                FE_DockGUIInvalidateDockOneDimention(api, dock, childDock, TRUE, rect, overflowCoef, &currentPos);
            }
        }

		break;
	case FE_GUI_DOCK_HORIZONTAL:
        if(dock->childrenDockId.impl.count > 0)
        {
            FE_GUIRect* rect = &FE_GUIQueryDockByID(api, dock->childrenDockId.data[dock->childrenDockId.impl.count - 1])->rect;
            Float32 overflowCoef;
            FE_GUIDock* childDock = NULL;
            Float32 currentPos = 0;
            for (SizeT i = 0; i < dock->childrenDockId.impl.count; i++)
            {
                overflowCoef = FE_DockGUIInvalidateOverflowCoefCalculation(i, rect->size.x, rect->position.x, dock->lastRect.position.x, dock->lastRect.size.x, dock->childrenDockId.impl.count);

                childDock = FE_GUIQueryDockByID(api, dock->childrenDockId.data[i]);
                FE_DockGUIInvalidateDockOneDimention(api, dock, childDock, FALSE, rect, overflowCoef, &currentPos);
            }
        }
		break;
	case FE_GUI_DOCK_TAB:
        if(dock->linkedOverlayId >= 0)
        {
            FE_GUIQueryOverlayByID(api,  dock->linkedOverlayId)->rect = dock->rect;
        }
		break;
	case FE_GUI_DOCK_UNKNOWN:
        if(dock->linkedOverlayId >= 0)
        {
            FE_GUIQueryOverlayByID(api,  dock->linkedOverlayId)->rect = dock->rect;
        }
		for (SizeT i = 0; i < dock->childrenDockId.impl.count; i++)
		{
			childDock = FE_GUIQueryDockByID(api, dock->childrenDockId.data[i]);

			if (childDock->linkedOverlayId >= 0)
			{
				FE_GUIQueryOverlayByID(api,  childDock->linkedOverlayId)->rect = childDock->rect;
			}
		}
		break;
	default:
		FE_CORE_ASSERT(FALSE, "unknown given dock type");
		break;
	}

    dock->lastRect = dock->rect;

	//if (linkedOverlayId == 0)
	//{
	//	WindowData* winData = &GetApp()->windowData;
	//	newRect->size.x = winData->w;
	//	newRect->size.y = winData->h;
	//}
	//else
	//{
	//	FE_GUIOverlay* baseOverlay = FE_GridLayoutQueryOverlayById(api, linkedOverlayId);
	//	switch (overlayPosition)
	//	{
	//	case FE_OVERLAY_POSITION_LEFT:
	//		newRect->size.x = baseOverlay->rect.size.x / 2;
	//		newRect->size.y = baseOverlay->rect.size.y;
	//		newRect->position.x = baseOverlay->rect.position.x;
	//		newRect->position.y = baseOverlay->rect.position.y;

	//		baseOverlay->rect.position.x += newRect->size.x;
	//		baseOverlay->rect.size.x = newRect->size.x;
	//		break;

	//	case FE_OVERLAY_POSITION_RIGHT:
	//		newRect->size.x = baseOverlay->rect.size.x / 2;
	//		newRect->size.y = baseOverlay->rect.size.y;
	//		newRect->position.x = baseOverlay->rect.position.x + newRect->size.x;
	//		newRect->position.y = baseOverlay->rect.position.y;

	//		baseOverlay->rect.size.x = newRect->size.x;
	//		break;

	//	case FE_OVERLAY_POSITION_BOTTOM:
	//		newRect->size.x = baseOverlay->rect.size.x;
	//		newRect->size.y = baseOverlay->rect.size.y / 2;
	//		newRect->position.x = baseOverlay->rect.position.x;
	//		newRect->position.y = baseOverlay->rect.position.y + newRect->size.y;

	//		baseOverlay->rect.size.y = newRect->size.y;
	//		break;

	//	case FE_OVERLAY_POSITION_TOP:
	//		newRect->size.x = baseOverlay->rect.size.x;
	//		newRect->size.y = baseOverlay->rect.size.y / 2;
	//		newRect->position.x = baseOverlay->rect.position.x;
	//		newRect->position.y = baseOverlay->rect.position.y;

	//		baseOverlay->rect.position.y += newRect->size.y;
	//		baseOverlay->rect.size.y = newRect->size.y;
	//		break;

	//	default:
	//		FE_CORE_LOG_ERROR("Given overlay position not supported");
	//		return;
	//	}

	//	if (overlayToDock->linkedDockId > 0)
	//	{
	//		FE_GUIOverlay* originalLinkedOverlay = FE_GridLayoutQueryOverlayById(api, overlayToDock->linkedDockId);
	//		originalLinkedOverlay->linkedDockId = 0;
	//	}

	//	baseOverlay->linkedDockId = overlayToDock->id;
	//	overlayToDock->linkedDockId = baseOverlay->id;

	//}

}

void FE_DECL FE_DockGUIChangeScale(NuklearGUIInterface* api, FE_GUIDock* dock, Float32 x, Float32 y, Float32 width, Float32 height)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(dock != NULL, "FE_GUIDock dock is NULL");
	FE_CORE_ASSERT(dock->isDestroyed == FALSE, "Given dock has been destroyed");

    dock->rect.position.x = x;
    dock->rect.position.y = y;

    dock->rect.size.x = width;
    dock->rect.size.y = height;

    FE_DockGUIRecursionInvalidateDock(api, dock);
}

void FE_DockGUIRecursionInvalidateDock(NuklearGUIInterface* api, FE_GUIDock* dock)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_CORE_ASSERT(dock != NULL, "FE_GUIDock dock is NULL");
	FE_CORE_ASSERT(dock->isDestroyed == FALSE, "Given dock has been destroyed");

	FE_DockGUIInvalidateDockRect(api, dock);
	for (SizeT i = 0; i < dock->childrenDockId.impl.count; i++)
	{
		FE_DockGUIRecursionInvalidateDock(api, FE_GUIQueryDockByID(api, dock->childrenDockId.data[i]));
	}
}

/*void FE_DockGUIUpdateScale(NuklearGUIInterface* api, FE_GUIDock* dock, FE_GUIOverlay* overlay)*/
/*{*/
/*	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");*/
/*	FE_CORE_ASSERT(dock != NULL, "FE_GUIDock dock is NULL");*/
/*	FE_CORE_ASSERT(dock->isDestroyed == FALSE, "Given dock has been destroyed");*/
/*	FE_CORE_ASSERT(overlay != NULL, "FE_GUIOverlay dock is NULL");*/
/*	FE_CORE_ASSERT(overlay->isDestroyed == FALSE, "Given overlay has been destroyed");*/
/**/
/*    const ILDA_vector2d* mousePos = GetCursorPosition();*/
/**/
/*    Bool cursorInbox = FE_IS_INBOX(mousePos->x, mousePos->y, 0, 0, GetApp()->windowData.w, GetApp()->windowData.h);*/
/**/
/*    if (cursorInbox)*/
/*    {*/
/*        Bool leftMouseDown = ((struct nk_context*)api->handle)->input.mouse.buttons[NK_BUTTON_LEFT].down;*/
/*        Bool isH = FALSE;*/
/*        Bool isMin = FALSE;*/
/**/
/*        if (FE_IS_ON_RIGHT_EDGE(mousePos->x, mousePos->y, overlay->rect.position.x, overlay->rect.position.y,*/
/*            overlay->rect.size.x, overlay->rect.size.y, FE_GUI_EDGE_MOUSE_DETECTION_TRESHOLD))*/
/*        {*/
/*            GetWindowAPI()->SetCursorShape(&GetApp()->windowData, FE_CURSOR_SHAPE_HRESIZE_CURSOR);*/
/*            isH = TRUE;*/
/*        }*/
/*        else if (FE_IS_ON_LEFT_EDGE(mousePos->x, mousePos->y, overlay->rect.position.x, overlay->rect.position.y,*/
/*            overlay->rect.size.y, FE_GUI_EDGE_MOUSE_DETECTION_TRESHOLD))*/
/*        {*/
/*            GetWindowAPI()->SetCursorShape(&GetApp()->windowData, FE_CURSOR_SHAPE_HRESIZE_CURSOR);*/
/*            isMin = TRUE;*/
/*            isH = TRUE;*/
/*        }*/
/*        else  if (FE_IS_ON_BOTTOM_EDGE(mousePos->x, mousePos->y, overlay->rect.position.x, overlay->rect.position.y,*/
/*            overlay->rect.size.x, overlay->rect.size.y, FE_GUI_EDGE_MOUSE_DETECTION_TRESHOLD))*/
/*        {*/
/*            GetWindowAPI()->SetCursorShape(&GetApp()->windowData, FE_CURSOR_SHAPE_VRESIZE_CURSOR);*/
/*            isH = 2;*/
/*        }*/
/*        else  if (FE_IS_ON_TOP_EDGE(mousePos->x, mousePos->y, overlay->rect.position.x, overlay->rect.position.y,*/
/*             overlay->rect.size.y, FE_GUI_EDGE_MOUSE_DETECTION_TRESHOLD))*/
/*        {*/
/*            GetWindowAPI()->SetCursorShape(&GetApp()->windowData, FE_CURSOR_SHAPE_VRESIZE_CURSOR);*/
/*            isMin = TRUE;*/
/*            isH = 2;*/
/*        }*/
/**/
/*        if (leftMouseDown)*/
/*        {*/
/*            if (isH && isMin)*/
/*            {*/
/*                Double distanceX = fabs(mousePos->x - overlay->rect.position.x);*/
/*                overlay->rect.position.x = (Float32)mousePos->x;*/
/*                overlay->rect.size.x += (Float32)distanceX;*/
/*            }*/
/*            else if (isH)*/
/*            {*/
/*                Double distanceX = (mousePos->x - (overlay->rect.position.x + overlay->rect.size.x));*/
/*                overlay->rect.size.x += (Float32)distanceX;*/
/*            }*/
/*            else if (isMin && isH == 2)*/
/*            {*/
/*                Double distanceY = fabs(overlay->rect.position.y - mousePos->y);*/
/*                overlay->rect.position.y = (Float32)mousePos->y;*/
/*                overlay->rect.size.y += (Float32)distanceY;*/
/*            }*/
/*            else if(isH == 2)*/
/*            {*/
/*                Double distanceY = (overlay->rect.position.y + overlay->rect.size.y - mousePos->y);*/
/*                overlay->rect.size.y += (Float32)distanceY;*/
/*            }*/
/*        }*/
/*    }*/
/*}*/

void FE_DockGUIDockOverlay(NuklearGUIInterface* api, Uint32 overlayToDockId, Uint32 baseDockSpaceId, FE_GUIOverlayPositions overlayPosition)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_GUIOverlay* overlayToDock = FE_GUIQueryOverlayByID(api, overlayToDockId);
	FE_GUIDockType newDockType = FE_GUI_DOCK_UNKNOWN;
	Float32 sliceProportion = 0.0f;

	switch (overlayPosition)
	{
	case FE_OVERLAY_POSITION_LEFT:
		newDockType = FE_GUI_DOCK_HORIZONTAL;
		sliceProportion = overlayToDock->rect.size.x / GetApp()->windowData.w;
		break;
	case FE_OVERLAY_POSITION_RIGHT:
		newDockType = FE_GUI_DOCK_HORIZONTAL;
		sliceProportion = overlayToDock->rect.size.x / GetApp()->windowData.w;
		break;
	case FE_OVERLAY_POSITION_TOP:
		newDockType = FE_GUI_DOCK_VERTICAL;
		sliceProportion = overlayToDock->rect.size.y / GetApp()->windowData.h;
		break;
	case FE_OVERLAY_POSITION_BOTTOM:
		newDockType = FE_GUI_DOCK_VERTICAL;
		sliceProportion =  overlayToDock->rect.size.y / GetApp()->windowData.h;
		break;
	case FE_OVERLAY_POSITION_CENTER:
		newDockType = FE_GUI_DOCK_TAB;
		sliceProportion = 1.0f;
		break;
	}

    FE_GUIDock* baseDock = FE_GUIQueryDockByID(api, baseDockSpaceId);
	if (api->guiDockLayout.docks.impl.count > baseDockSpaceId && !api->guiDockLayout.docks.data[baseDockSpaceId].isDestroyed)
	{
		if (baseDock->type == FE_GUI_DOCK_UNKNOWN)
		{
			baseDock->type = newDockType;
		}

		FE_CORE_ASSERT(baseDock->type == newDockType, "Dock type is not correct");
	}
	else
	{
		FE_CORE_ASSERT(FALSE, "The given dock base does not exists");
	}

	if (newDockType != FE_GUI_DOCK_TAB && (baseDock->linkedOverlayId >= 0 || baseDock->childrenDockId.impl.count > 0))
	{
		SizeT newSliceId = FE_DockGUISlice(api, baseDockSpaceId, overlayPosition, sliceProportion);
		api->guiDockLayout.docks.data[newSliceId].linkedOverlayId = overlayToDockId;
		//FE_DockGUIGetByID(api, baseDockSpaceId)->childrenDockId.data[newSliceId] = FE_DockGUIGetByID(api, baseDockSpaceId)->id;
		//api->guiDockLayout.docks.data[FE_DockGUIGetByID(api, baseDockSpaceId)->childrenDockId.data[newSliceId]].linkedOverlay = overlayToDock;
	}
	else
	{
		FE_GUIQueryDockByID(api, baseDockSpaceId)->linkedOverlayId = overlayToDockId;
	}

    FE_GUIQueryOverlayByID(api, overlayToDockId)->flags &= ~FE_OVERLAY_MOVABLE;
	FE_DockGUIInvalidateDockRect(api, FE_GUIQueryDockByID(api, baseDockSpaceId));
}

void FE_DockGUIUndockOverlay(NuklearGUIInterface* api, Uint32 overlayToUndockID)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

    FE_GUIDock* dock = NULL;

    for(SizeT i = 0; i < api->guiDockLayout.docks.impl.count; i++)
    {
        if(FE_GUIQueryDockByID(api, i)->linkedOverlayId == overlayToUndockID)
        {
            dock = FE_GUIQueryDockByID(api, i);
            break;
        }
    }

    if(dock != NULL && dock->parentID >= 0)
    {
        FE_GUIQueryOverlayByID(api, overlayToUndockID)->flags |= FE_OVERLAY_MOVABLE;
        FE_GUIDock* parentDock = FE_GUIQueryDockByID(api, dock->parentID);
        FE_ListRemove(parentDock->childrenDockId, dock->id);
        if(parentDock->childrenDockId.impl.count == 1)
        {
            FE_GUIDock* firstContentDock = FE_GUIQueryDockByID(api, *(SizeT*)FE_ListGet(parentDock->childrenDockId, 0));
            if(firstContentDock->linkedOverlayId < 0)
            {
                parentDock->childrenDockId.data = firstContentDock->childrenDockId.data;
                parentDock->childrenDockId.impl = firstContentDock->childrenDockId.impl;
                parentDock->type = firstContentDock->type;
                for(SizeT i = 0; i < parentDock->childrenDockId.impl.count; i++)
                {
                    FE_GUIQueryDockByID(api, *(SizeT*)FE_ListGet(parentDock->childrenDockId, i))->parentID = parentDock->id;
                }
            }
            else
            {
                parentDock->linkedOverlayId = firstContentDock->linkedOverlayId;
                parentDock->type = FE_GUI_DOCK_UNKNOWN;
            }

            FE_DockGUIDestroy(api, firstContentDock->id);
        }
        FE_DockGUIRecursionInvalidateDock(api, parentDock);
    }

}

FE_GUIOverlay* FE_GUIQueryOverlayByID(const NuklearGUIInterface* api, Uint32 overlayId)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");
	FE_GUIOverlay* overlay = FE_ListGet(api->guiDockLayout.overlays, overlayId);
    FE_CORE_ASSERT(overlay != NULL, "requested overlay does not exist");
    return overlay;
}

// nuklear convert
//nk_flags FE_NuklearConvertOverlayFlags(FE_GUIOvelayFlags feFlags)
//{
//	nk_flags result = 0;o
//
//	nk_flags nuklearPanelFlags[] = {//translated order
//		NK_WINDOW_BORDER,
//		NK_WINDOW_MOVABLE,
//		NK_WINDOW_SCALABLE,
//		NK_WINDOW_CLOSABLE,
//		NK_WINDOW_MINIMIZABLE,
//		NK_WINDOW_NO_SCROLLBAR,
//		NK_WINDOW_TITLE,
//		NK_WINDOW_SCROLL_AUTO_HIDE,
//		NK_WINDOW_BACKGROUND,
//		NK_WINDOW_SCALE_LEFT,
//		NK_WINDOW_NO_INPUT
//	};
//
//	for (Int32 i = 0; i < FE_WINDOW_FLAGS_LENGTH; i++)
//	{
//		if (feFlags & BIT(i))
//		{
//			result |= nuklearPanelFlags[i];
//		}
//	}
//
//	return result;
//}

// window
Bool FE_OverlayGUIBegin(const NuklearGUIInterface* api, Uint32 overlayId)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_GUIOverlay* overlay = FE_GUIQueryOverlayByID(api, overlayId);

	if (!overlay->isDestroyed && overlay->isVisible)
	{
        /*FE_DockGUIUpdateScale(api, FE_ListGet(api->guiDockLayout.docks, 0), overlay);*/
        overlay->isReady = nk_begin(((struct nk_context*)api->handle), overlay->name, nk_rect(overlay->rect.position.x, overlay->rect.position.y, overlay->rect.size.x, overlay->rect.size.y), overlay->flags);

		return overlay->isReady;
	}

	return FALSE;
}

void FE_OverlayGUIEnd(const NuklearGUIInterface* api, Uint32 overlayId)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_GUIOverlay* overlay = FE_GUIQueryOverlayByID(api, overlayId);

	overlay->isReady = FALSE;

	nk_end(api->handle);
}

void FE_OverlayGUISetVisibility(FE_GUIOverlay* overlay, Bool visibility)
{
	FE_CORE_ASSERT(overlay != NULL, "FE_GUIOverlay overlay is NULL");
	overlay->isVisible = visibility;
}

void FE_PropertyGUIVector3Field(NuklearGUIInterface* api, ILDA_vector3f* vec3)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	nk_layout_row_dynamic(api->handle, 20, 4);
	nk_property_float(api->handle, "#x", -FE_FLOAT_MAX_PRECISION, &vec3->x, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(api->handle, "#y", -FE_FLOAT_MAX_PRECISION, &vec3->y, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(api->handle, "#z", -FE_FLOAT_MAX_PRECISION, &vec3->z, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
}

void FE_PropertyGUITransformField(NuklearGUIInterface* api, FE_CompTransform3D* tr)
{
	FE_CORE_ASSERT(api != NULL, "NuklearGUIInterface api is NULL");

	FE_PropertyGUIVector3Field(api, &tr->position);
    FE_PropertyGUIVector3Field(api, &tr->rotation);
    FE_PropertyGUIVector3Field(api, &tr->scale);
}
