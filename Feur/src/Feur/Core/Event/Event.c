#include "fepch.h"
#include "Event.h"

void DispatchEvent(FE_EventDispatcher* eventDispatcher, FE_EventType eventType)
{
	if (eventDispatcher->eventType == eventType)
	{
		eventDispatcher->event.isHandled = TRUE;
		eventDispatcher->f(&eventDispatcher->event.eventData);
	}
}

BOOL IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event)
{
	if (eventCategory | event->eventCategory)
	{
		return TRUE;
	}

	return FALSE;
}