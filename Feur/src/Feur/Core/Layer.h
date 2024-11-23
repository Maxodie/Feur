#pragma once

typedef struct Layer
{
	char* layerName;
	void (*OnUpdateLayerEvent)(FE_Event*);
	void (*OnUpdate)(Double deltaTime);
	void (*OnNuklearRender)(struct NuklearGUIInterface* interface, struct Layer* layer);
	void (*OnWindowResized)(Uint32 width, Uint32 height);

	void (*OnAttach)(struct Layer* layer);
	void (*OnDetach)();

	void* handledInfo;
} Layer;