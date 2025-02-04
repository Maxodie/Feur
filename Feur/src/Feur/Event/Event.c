#include "fepch.h"
#include "Feur/Event/Event.h"

void FE_DECL FE_EventSystemInit(FE_EventRegistry* registry)
{
	FE_ListInit(registry->table);
	FE_ListInit(registry->tasks);
}

void FE_DECL FE_EventSystemClear(FE_EventRegistry* registry)
{
	FE_ListClear(registry->tasks);
	FE_ListClear(registry->table);
}

FE_EventID FE_DECL FE_EventAttach(FE_EventRegistry* registry, FE_EventType eventType, Bool(*callback)(FE_EventData*))
{
	FE_EventRegistryTable table = { .eventType = eventType, .callback = callback, .FE_EventID = registry->maxUuid++};
	FE_ListPush(registry->table, table);
	return  registry->maxUuid;
}

void FE_DECL FE_EventDetach(FE_EventRegistry* registry, FE_EventID id)
{
	for (SizeT i = 0; i < registry->table.impl.count; i++)
	{
		if (registry->table.data[i].FE_EventID == id)
		{
			FE_ListRemoveAt(registry->table, id);
			return;
		}
	}
}

void FE_DECL FE_EventDispatch(FE_EventRegistry* registry, FE_Event* event)
{
	for (SizeT i = 0; i < registry->table.impl.count; i++)
	{
		if (event->eventType == registry->table.data[i].eventType)
		{
			event->isHandled = registry->table.data[i].callback(&event->eventData);
		}
	}
}

void FE_DECL FE_EventPostTask(FE_EventRegistry* registry, void(*task)())
{
	FE_ListPush(registry->tasks, task);
}

void FE_DECL FE_EventPollTask(FE_EventRegistry* registry)
{
	for (Int32 i = registry->tasks.impl.count - 1; i >= 0; i--)
	{
		registry->tasks.data[i].f();
		FE_ListPop(registry->tasks);
	}
}

Bool FE_DECL IsEventInCategory(const FE_EventCategory eventCategory, FE_Event* event)
{
	return (eventCategory | event->eventCategory);
}