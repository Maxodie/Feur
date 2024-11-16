#pragma once

typedef struct Layer
{
	char* layerName;
	void (*OnUpdateLayerEvent)(FE_Event*);
	void (*OnUpdate)(Double deltaTime);
	void (*OnNuklearRender)(struct Layer* layer);

	void (*OnAttach)(struct Layer* layer);
	void (*OnDetach)();

	void* handledInfo;
} Layer;