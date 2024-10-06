#include "fepch.h"
#include "Event.h"

void FE_API DispatchEvent(FE_EventDispatcher* eventDispatcher, FE_EventType eventType, void(*f)(FE_EventData*))
{
	if (eventDispatcher->eventType == eventType)
	{
		eventDispatcher->event.isHandled = TRUE;
		f(&eventDispatcher->event.eventData);
	}
}

BOOL FE_API IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event)
{
	if (eventCategory | event->eventCategory)
	{
		return TRUE;
	}

	return FALSE;
}