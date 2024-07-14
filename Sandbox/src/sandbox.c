#include "Feur.h"

void UpdateSandboxLayerBase();
void UpdateLayerBaseEventSandbox(FE_Event* event);
void OnAttachSandboxLayerBase();



void StartSandbox()
{
	FE_LOG_DEBUG("Add Sandbox base layer to the stack");
	AddLayerApp(&layer);
}

void UpdateSandboxLayerBase()
{
	if (IsInputPressed(FE_KEYCODE_H))
	{
		FE_LOG_WARNING("test : %d", 50);
	}
}


void UpdateLayerBaseEventSandbox(FE_Event* event)
{
	FE_LOG_WARNING("resize ");
}

void OnAttachSandboxLayerBase()
{
	FE_LOG_DEBUG("Sandbox base layer attached");
}