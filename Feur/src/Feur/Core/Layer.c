#include "fepch.h"

#include "Feur/Core/Layer.h"

void FE_API UpdateLayerEvent(Layer* layer, FE_Event* event)
{
	FE_CORE_LOG_DEBUG("layer update Event : %s", layer->layerName);
	layer->OnUpdateLayerEvent(event);
}
