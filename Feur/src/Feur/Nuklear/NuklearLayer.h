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
	FE_OVERLAY_POSITION_UP,
	FE_OVERLAY_POSITION_DOWN,
	FE_OVERLAY_POSITION_CENTER,
} FE_GUIOverlayPositions;

typedef struct FE_GUIOverlayRect
{
	ILDA_vector2f position;
	ILDA_vector2f size;
} FE_GUIOverlayRect;

typedef struct FE_GUIOverlay
{
	const char* name;
	Bool isReady;
	FE_GUIOverlayRect rect;
	FE_GUIOvelayFlags flags;

	Uint16 overlayId;
} FE_GUIOverlay;

typedef struct FE_GUIGridLayout
{
	FE_List(FE_GUIOverlay*) overlays;
	
} FE_GUIGridLayout;

typedef struct NuklearGUIInterface
{
	void (*Init)(struct NuklearGUIInterface* interface);
	void (*OnEvent)(FE_Event*);
	void (*OnBeginRender)(struct NuklearGUIInterface* interface);
	void (*OnEndRender)(struct NuklearGUIInterface* interface);
	void (*Shutdown)();

	void (*OnWindowResize)(Uint32 width, Uint32 height);

	void* handle;
	FE_GUIGridLayout guiGridLayout;
	Uint32 overlayGUIMaxID;
} NuklearGUIInterface;



void FE_DECL NuklearGUIInterfaceInit(NuklearGUIInterface* api); 
void FE_DECL NuklearGUIInterfaceShutdown(NuklearGUIInterface* api);
void FE_DECL NuklearGUIBeginRender();
void FE_DECL NuklearGUIEndRender();
Bool FE_DECL NuklearGUIInputLayerCheck(const NuklearGUIInterface* api);

// grid layout
void FE_DECL FE_GridLayoutGUIInsertOverlay(NuklearGUIInterface* api, FE_GUIOverlay* outOverlay, const char* name, FE_GUIOvelayFlags flags);
void FE_DECL FE_GridLayoutGUIRemoveOverlay(NuklearGUIInterface* api, const FE_GUIOverlay* overlayToRemove);

void FE_DECL FE_GridLayoutGUIDockOverlay(NuklearGUIInterface* api, FE_GUIOverlay* overlayToDock, Uint32 baseOverlayID, FE_GUIOverlayPositions overlayPosition);

// window
Bool FE_DECL FE_OverlayGUIBegin(const NuklearGUIInterface* api, FE_GUIOverlay* overlay);
void FE_DECL FE_OverlayGUIEnd(const NuklearGUIInterface* api, FE_GUIOverlay* overlay);

// properties
void FE_DECL FE_PropertyGUIVector3Field(NuklearGUIInterface* api, const ILDA_vector3f* vec3); 

void FE_DECL FE_PropertyGUITransformField(NuklearGUIInterface* api, const FE_CompTransform3D* tr);