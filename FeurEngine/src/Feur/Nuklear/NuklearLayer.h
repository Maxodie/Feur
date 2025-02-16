#pragma once

typedef enum FE_GUIOvelayFlags
{
	FE_OVERLAY_BORDER = BIT(0),
	FE_OVERLAY_MOVABLE = BIT(1),
	FE_OVERLAY_SCALABLE = BIT(2),
	FE_OVERLAY_CLOSABLE = BIT(3),
	FE_OVERLAY_MINIMIZABLE = BIT(4),
	FE_OVERLAY_NO_SCROLLBAR = BIT(5),
	FE_OVERLAY_TITLE = BIT(6),
	FE_OVERLAY_SCROLL_AUTO_HIDE = BIT(7),
	FE_OVERLAY_BACKGROUND = BIT(8),
	FE_OVERLAY_SCALE_LEFT = BIT(9),
	FE_OVERLAY_NO_INPUT = BIT(10),
	FE_OVERLAY_FLAGS_LENGTH
} FE_GUIOvelayFlags;

typedef enum FE_GUIOverlayPositions
{
	FE_OVERLAY_POSITION_LEFT,
	FE_OVERLAY_POSITION_RIGHT,
	FE_OVERLAY_POSITION_TOP,
	FE_OVERLAY_POSITION_BOTTOM,
	FE_OVERLAY_POSITION_CENTER,
} FE_GUIOverlayPositions;

typedef enum FE_GUIDockType
{
	FE_GUI_DOCK_UNKNOWN,
	FE_GUI_DOCK_VERTICAL,
	FE_GUI_DOCK_HORIZONTAL,
	FE_GUI_DOCK_TAB,
} FE_GUIDockType;

typedef struct FE_GUIRect
{
	ILDA_vector2f position;
	ILDA_vector2f size;
} FE_GUIRect;

typedef struct FE_GUIOverlay
{
	Bool isDestroyed;
	const char* name;
	Bool isReady;
	Bool isVisible;
	SizeT id;
	FE_GUIRect rect;
	FE_GUIOvelayFlags flags;

} FE_GUIOverlay;

typedef struct FE_GUIDock
{
	Bool isDestroyed;
	FE_GUIRect rect;
	SizeT linkedOverlayId;
	FE_GUIDockType type;
	SizeT id;
	FE_List(SizeT) childrenDockId;
} FE_GUIDock;

typedef struct FE_GUIGridLayout
{
	FE_List(FE_GUIOverlay) overlays;
	FE_List(FE_GUIDock) docks;
} FE_GUIGridLayout;

typedef struct NuklearGUIInterface
{
	void (*Init)(struct NuklearGUIInterface* interface);
	void (*OnEvent)(FE_Event*);
	void (*OnBeginRender)(struct NuklearGUIInterface* interface);
	void (*OnEndRender)();
	void (*Shutdown)();

	void (*OnWindowResize)(Uint32 width, Uint32 height);

	void* handle;
	Uint32 baseOverlay;
	FE_GUIGridLayout guiDockLayout;
	Uint32 overlayGUIMaxID;
} NuklearGUIInterface;



void FE_DECL NuklearGUIInterfaceInit(NuklearGUIInterface* api);
void FE_DECL NuklearGUIInterfaceShutdown(NuklearGUIInterface* api);
void FE_DECL NuklearGUIBeginRender();
void FE_DECL NuklearGUIEndRender();
Bool FE_DECL NuklearGUIInputLayerCheck(const NuklearGUIInterface* api);

// visualization
void FE_DECL FE_DockGUIPrintCurrentState(NuklearGUIInterface* api);

// dock layout
void FE_DECL FE_DockGUIInit(NuklearGUIInterface* api);
void FE_DECL FE_DockGUIShutdown(NuklearGUIInterface* api);

SizeT FE_DECL FE_DockGUICreate(NuklearGUIInterface* api, FE_GUIDockType dockType, const FE_GUIRect* rect);
SizeT FE_DECL FE_DockGUISlice(NuklearGUIInterface* api, SizeT dockId, FE_GUIOverlayPositions position, Float32 sliceProportion);
void FE_DECL FE_DockGUIDestroy(NuklearGUIInterface* api, SizeT dockId);

void FE_DECL FE_DockGUIInvalidateDocks(NuklearGUIInterface* api);
void FE_DECL FE_DockGUIInvalidateDockRect(NuklearGUIInterface* api, FE_GUIDock* dock);

void FE_DECL FE_DockGUIDockOverlay(NuklearGUIInterface* api, Uint32 overlayToDockId, Uint32 baseDockSpaceId, FE_GUIOverlayPositions overlayPosition);
void FE_DECL FE_DockGUIUndockOverlay(NuklearGUIInterface* api, FE_GUIOverlay* overlayToUndock);

// query
FE_GUIOverlay* FE_DECL FE_GUIQueryOverlayByID(const NuklearGUIInterface* api, Uint32 overlayId);
FE_GUIDock* FE_DECL FE_GUIQuesryDockByID(NuklearGUIInterface* api, SizeT dockId);

// window
Bool FE_DECL FE_OverlayGUIBegin(const NuklearGUIInterface* api, Uint32 overlayId);
void FE_DECL FE_OverlayGUIEnd(const NuklearGUIInterface* api, Uint32 overlayId);

Uint32 FE_DECL FE_GUICreateOverlay(NuklearGUIInterface* api, const char* name);
void FE_DECL FE_DockGUIDestroyOverlay(NuklearGUIInterface* api, FE_GUIOverlay* overlayToRemove);
void FE_DECL FE_OverlayGUISetVisibility(FE_GUIOverlay* overlay, Bool visibility);

// properties
void FE_DECL FE_PropertyGUIVector3Field(NuklearGUIInterface* api, ILDA_vector3f* vec3);

void FE_DECL FE_PropertyGUITransformField(NuklearGUIInterface* api, FE_CompTransform3D* tr);
