#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include <Nuklear/nuklear.h>
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"

void NuklearGUIInterfaceInit(NuklearGUIInterface* api)
{
	api->overlayGUIMaxID = 0;
	FE_ListInit(api->guiGridLayout.overlays);
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
	FE_ListClear(api->guiGridLayout.overlays);
}

void NuklearGUIBeginRender()
{
	GetApp()->guiInterface.OnBeginRender(&GetApp()->guiInterface);
}

void NuklearGUIEndRender()
{
	GetApp()->guiInterface.OnEndRender(&GetApp()->guiInterface);
}

Bool NuklearGUIInputLayerCheck(const NuklearGUIInterface* api)
{
    struct nk_context* context = (struct nk_context*)api->handle;
    if (context == NULL) return FALSE;
    return (context->last_widget_state & NK_WIDGET_STATE_MODIFIED);
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

void FE_DECL FE_GridLayoutGUIInsertOverlay(NuklearGUIInterface* api, FE_GUIOverlay* outOverlay, const char* name, FE_GUIOvelayFlags flags)
{
	outOverlay->flags = flags;
	outOverlay->name = name;
	outOverlay->overlayId = ++api->overlayGUIMaxID;

	FE_ListPush(api->guiGridLayout.overlays, outOverlay);
}

void FE_DECL FE_GridLayoutGUIRemoveOverlay(NuklearGUIInterface* api, const FE_GUIOverlay* overlayToRemove)
{
	FE_ListRemove(api->guiGridLayout.overlays, overlayToRemove);
}

void FE_DECL FE_GridLayoutGUIDockOverlay(NuklearGUIInterface* api, FE_GUIOverlay* overlayToDock, Uint32 baseOverlayID, FE_GUIOverlayPositions overlayPosition)
{
	FE_GUIOverlayRect* newRect = &overlayToDock->rect;

	if (baseOverlayID == 0)
	{
		newRect->size.x = GetApp()->windowData.w;
		newRect->size.y = GetApp()->windowData.h;
	}
	else
	{
		FE_GUIOverlay** baseOverlay = api->guiGridLayout.overlays.data;
		SizeT overlayCount = api->guiGridLayout.overlays.impl.count;
		for (SizeT i = 0; i < overlayCount; i++)
		{
			if (baseOverlay[i]->overlayId == baseOverlayID)
			{
				switch (overlayPosition)
				{
				case FE_OVERLAY_POSITION_LEFT:
					newRect->size.x = baseOverlay[i]->rect.size.x / 2;
					newRect->size.y = baseOverlay[i]->rect.size.y;
					newRect->position.x = baseOverlay[i]->rect.position.x;
					newRect->position.y = baseOverlay[i]->rect.position.y;

					baseOverlay[i]->rect.position.x += newRect->size.x;
					baseOverlay[i]->rect.size.x = newRect->size.x;
					break;

				case FE_OVERLAY_POSITION_RIGHT:
					newRect->size.x = baseOverlay[i]->rect.size.x / 2;
					newRect->size.y = baseOverlay[i]->rect.size.y;
					newRect->position.x = baseOverlay[i]->rect.position.x + newRect->size.x;
					newRect->position.y = baseOverlay[i]->rect.position.y;

					baseOverlay[i]->rect.size.x = newRect->size.x;
					break;

				case FE_OVERLAY_POSITION_DOWN:
					newRect->size.x = baseOverlay[i]->rect.size.x;
					newRect->size.y = baseOverlay[i]->rect.size.y / 2;
					newRect->position.x = baseOverlay[i]->rect.position.x;
					newRect->position.y = baseOverlay[i]->rect.position.y + newRect->size.y;

					baseOverlay[i]->rect.size.y = newRect->size.y;
					break;

				case FE_OVERLAY_POSITION_UP:
					newRect->size.x = baseOverlay[i]->rect.size.x;
					newRect->size.y = baseOverlay[i]->rect.size.y / 2;
					newRect->position.x = baseOverlay[i]->rect.position.x;
					newRect->position.y = baseOverlay[i]->rect.position.y;

					baseOverlay[i]->rect.position.y += newRect->size.y;
					baseOverlay[i]->rect.size.y = newRect->size.y;
					break;

				default:
					FE_CORE_LOG_ERROR("Given overlay position not supported");
					break;
				}
			}
		}
	}
}

// window
Bool FE_OverlayGUIBegin(const NuklearGUIInterface* api, FE_GUIOverlay* overlay)
{
	struct nk_context* context = (struct nk_context*)api->handle;

	return overlay->isReady = nk_begin(context, overlay->name, nk_rect(overlay->rect.position.x, overlay->rect.position.y, overlay->rect.size.x, overlay->rect.size.y), overlay->flags);
}

void FE_OverlayGUIEnd(const NuklearGUIInterface* api, FE_GUIOverlay* overlay)
{
	struct nk_context* context = (struct nk_context*)api->handle;
	
	overlay->isReady = FALSE;

	nk_end(context);
}

void FE_PropertyGUIVector3Field(NuklearGUIInterface* api, const ILDA_vector3f* vec3)
{
	nk_layout_row_dynamic(api->handle, 20, 4);
	nk_property_float(api->handle, "#x", -FE_FLOAT_MAX_PRECISION, &vec3->x, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(api->handle, "#y", -FE_FLOAT_MAX_PRECISION, &vec3->y, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(api->handle, "#z", -FE_FLOAT_MAX_PRECISION, &vec3->z, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
}

void FE_PropertyGUITransformField(NuklearGUIInterface* api, const FE_CompTransform3D* tr)
{
    FE_PropertyGUIVector3Field(api, &tr->position);
    FE_PropertyGUIVector3Field(api, &tr->rotation);
    FE_PropertyGUIVector3Field(api, &tr->scale);
}
