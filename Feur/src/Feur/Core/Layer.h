#pragma once

typedef struct Layer
{
	char* layerName;
	void (*OnUpdateLayerEvent)(FE_Event*);
	void (*OnUpdate)();

	void (*OnAttach)();
} Layer;