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
	int w, h;
} FE_EventData;

typedef struct FE_Event {
	FE_EventType eventType;
	FE_EventCategory eventCategory;
	BOOL isHandled;
	FE_EventData eventData;// pas bien ):
} FE_Event;

typedef struct FE_EventDispatcher {
	FE_EventType eventType;
	void(*f)(FE_EventData*);

	FE_Event event;
}FE_EventDispatcher;

void DispatchEvent(FE_EventDispatcher* eventDispatcher, FE_EventType eventType);
BOOL IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event);