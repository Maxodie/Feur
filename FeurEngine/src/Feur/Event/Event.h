#pragma once

typedef enum FE_EventType
{
	FE_Event_None,
	FE_Event_WindowClose, FE_Event_WindowResize, FE_Event_WindowFocus, FE_Event_WindowLostFocus, FE_Event_WindowMoved,
	FE_Event_AppTick, FE_Event_AppUpdate, FE_Event_AppRender,
	FE_Event_KeyPressed, FE_Event_KeyReleased, FE_Event_KeyTyped,
	FE_Event_MouseButtonPressed, FE_Event_MouseButtonReleased, FE_Event_MouseMoved, FE_Event_MouseScrolled
}FE_EventType;

typedef enum FE_EventCategory {
	FE_EventCategory_None = 0,
	FE_EventCategory_Application = BIT(0),
	FE_EventCategory_Input = BIT(1),
	FE_EventCategory_EventCategoryKeyboard = BIT(2),
	FE_EventCategory_EventCategoryMouse = BIT(3),
	FE_EventCategory_EventCategoryMouseButton = BIT(4)
} FE_EventCategory;

typedef struct FE_EventData {
	WindowData* windowData;
} FE_EventData;

typedef struct FE_EventTask
{
	void (*f)();
} FE_EventTask;

typedef struct FE_Event {
	FE_EventType eventType;
	FE_EventCategory eventCategory;
	FE_EventData eventData;
	Bool isHandled;
} FE_Event;

typedef Uint64 FE_EventID;

typedef struct FE_EventRegistryTable
{
	FE_EventType eventType;
	FE_EventID FE_EventID;
	Bool (*callback)(FE_EventData*);
} FE_EventRegistryTable;

typedef struct FE_EventRegistry
{
	FE_List(FE_EventTask) tasks;
	FE_List(FE_EventRegistryTable) table;
	FE_EventID maxUuid;
} FE_EventRegistry;


void FE_DECL FE_EventSystemInit(FE_EventRegistry* registry);
void FE_DECL FE_EventSystemClear(FE_EventRegistry* registry);

FE_EventID FE_DECL FE_EventAttach(FE_EventRegistry* registry, FE_EventType eventType, Bool(*callback)(FE_EventData*));
void FE_DECL FE_EventDetach(FE_EventRegistry* registry, FE_EventID id);

void FE_DECL FE_EventDispatch(FE_EventRegistry* registry, FE_Event* event);

void FE_DECL FE_EventPostTask(FE_EventRegistry* registry, void(*task)());
void FE_DECL FE_EventPollTask(FE_EventRegistry* registry);

Bool FE_DECL IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event);