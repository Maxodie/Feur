#pragma once

typedef struct NuklearGUIInterface
{
	void (*Init)(struct NuklearGUIInterface* interface);
	void (*OnEvent)(FE_Event*);
	void (*OnBeginRender)(struct NuklearGUIInterface* interface);
	void (*OnEndRender)(struct NuklearGUIInterface* interface);
	void (*Shutdown)();

	void (*OnWindowResize)(Uint32 width, Uint32 height);

	void* handle;

} NuklearGUIInterface;

typedef enum FE_GUIOvelayFlags
{

	FE_WINDOW_BORDER = BIT(0),
	FE_WINDOW_MOVABLE = BIT(1),
	FE_WINDOW_SCALABLE = BIT(2),
	FE_WINDOW_CLOSABLE = BIT(3),
	FE_WINDOW_MINIMIZABLE = BIT(4),
	FE_WINDOW_NO_SCROLLBAR = BIT(5),
	FE_WINDOW_TITLE = BIT(6),
	FE_WINDOW_SCROLL_AUTO_HIDE = BIT(7),
	FE_WINDOW_BACKGROUND = BIT(8),
	FE_WINDOW_SCALE_LEFT = BIT(9),
	FE_WINDOW_NO_INPUT = BIT(10),
	FE_WINDOW_FLAGS_LENGTH
} FE_GUIOvelayFlags;

typedef struct FE_GUIOverlay
{
	Uint32 width;
	Uint32 height;
	Uint32 id;
} FE_GUIOverlay;

typedef struct FE_GUIGridSpace
{
	FE_List(FE_GUIOverlay) windows;
} FE_GUIGridSpace;

void FE_DECL NuklearGUIInterfaceInit(NuklearGUIInterface* interface); 
void FE_DECL NuklearGUIBeginRender(); 
void FE_DECL NuklearGUIEndRender();
Bool FE_DECL NuklearGUIInputLayerCheck(const NuklearGUIInterface* interface);

// window
Bool FE_DECL FE_OverlayGUIBegin(NuklearGUIInterface* interface, const char* windowName, Uint32 width, Uint32 height, FE_GUIOvelayFlags flags);
void FE_DECL FE_OverlayGUIEnd(NuklearGUIInterface* interface);

// properties
void FE_DECL FE_PropertyGUIVector3Field(NuklearGUIInterface* interface, const ILDA_vector3f* vec3); 

void FE_DECL FE_PropertyGUITransformField(NuklearGUIInterface* interface, const FE_CompTransform3D* tr);