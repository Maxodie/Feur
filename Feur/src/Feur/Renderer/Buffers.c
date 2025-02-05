#include "fepch.h"
#include "Feur/Renderer/Buffers.h"

void FE_DECL FE_FrameBufferSetup(FE_FrameBuffer* frameBuffer, Uint32 w, Uint32 h)
{
	frameBuffer->h = h;
	frameBuffer->w = w;
	frameBuffer->posX = 0;
	frameBuffer->posY = 0;
}
