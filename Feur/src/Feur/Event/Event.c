#include "fepch.h"
#include "Feur/Event/Event.h"

void FE_DECL DispatchEvent(FE_EventDispatcher* eventDispatcher, FE_EventType eventType, void(*f)(FE_EventData*))
{
	if (eventDispatcher->eventType == eventType)
	{
		eventDispatcher->event.isHandled = TRUE;
		f(&eventDispatcher->event.eventData);
	}
}

Bool FE_DECL IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event)
{
	if (eventCategory | event->eventCategory)
	{
		return TRUE;
	}

	return FALSE;
}