#include "fepch.h"
#include "Feur/Nuklear/NuklearLayer.h"
#include <Nuklear/nuklear.h>
#include "Platform/Nuklear/OpenGLNuklearLayer.h"
#include "Platform/Nuklear/VulkanNuklearLayer.h"

void NuklearGUIInterfaceInit(NuklearGUIInterface* interface)
{
	if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_OPENGL)
	{
		interface->Init = OpenGL_GLFW_NuklearGUIInit_impl;
		interface->Shutdown = OpenGL_GLFW_NuklearGUIShutdown_impl;
		interface->OnEvent = OpenGL_GLFW_NuklearGUIEvent_impl;
		interface->OnEndRender = OpenGL_GLFW_NuklearGUIEndRender_impl;
	}
	else if (GetWindowAPI()->API_Type == FE_WINDOW_API_GLFW && GetRendererAPI()->API_Type == FE_RENDERER_API_TYPE_VULKAN)
	{
		interface->Init = Vulkan_GLFW_NuklearGUIInit_impl;
		interface->Shutdown = Vulkan_GLFW_NuklearGUIShutdown_impl;
		interface->OnEvent = Vulkan_GLFW_NuklearGUIEvent_impl;
		interface->OnBeginRender = Vulkan_GLFW_NuklearGUIBeginRender_impl;
		interface->OnEndRender = Vulkan_GLFW_NuklearGUIEndRender_impl;
		interface->OnWindowResize = Vulkan_GLFW_NuklearGUIOnWindowResize_impl;
	}
}

void NuklearGUIBeginRender()
{
	GetApp()->guiInterface.OnBeginRender(&GetApp()->guiInterface);
}

void NuklearGUIEndRender()
{
	GetApp()->guiInterface.OnEndRender(&GetApp()->guiInterface);
}

Bool FE_DECL NuklearGUIInputLayerCheck(const NuklearGUIInterface* interface)
{
    struct nk_context* context = (struct nk_context*)interface->handle;
    if (context == NULL) return FALSE;
    return (context->last_widget_state & NK_WIDGET_STATE_MODIFIED);
}

// nuklear convert
//nk_flags FE_NuklearConvertOverlayFlags(FE_GUIOvelayFlags feFlags)
//{
//	nk_flags result = 0;
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
Bool FE_DECL FE_OverlayGUIBegin(NuklearGUIInterface* interface, const char* windowName, Uint32 width, Uint32 height, FE_GUIOvelayFlags flags)
{
	struct nk_context* context = (struct nk_context*)interface->handle;

	return nk_begin(context, windowName, nk_rect(0, 0, width, height), flags);
}

void FE_DECL FE_OverlayGUIEnd(NuklearGUIInterface* interface)
{
	struct nk_context* context = (struct nk_context*)interface->handle;
	
	nk_end(context);
}

void FE_DECL FE_PropertyGUIVector3Field(NuklearGUIInterface* interface, const ILDA_vector3f* vec3)
{
	nk_layout_row_dynamic(interface->handle, 20, 4);
	nk_property_float(interface->handle, "#x", -FE_FLOAT_MAX_PRECISION, &vec3->x, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(interface->handle, "#y", -FE_FLOAT_MAX_PRECISION, &vec3->y, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
	nk_property_float(interface->handle, "#z", -FE_FLOAT_MAX_PRECISION, &vec3->z, FE_FLOAT_MAX_PRECISION, 0.05f, 0.05f);
}

void FE_DECL FE_PropertyGUITransformField(NuklearGUIInterface* interface, const FE_CompTransform3D* tr)
{
    FE_PropertyGUIVector3Field(interface, &tr->position);
    FE_PropertyGUIVector3Field(interface, &tr->rotation);
    FE_PropertyGUIVector3Field(interface, &tr->scale);
}
