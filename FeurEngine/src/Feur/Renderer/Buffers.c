#include "fepch.h"
#include "Feur/Renderer/Buffers.h"

void FE_DECL FE_FrameBufferResize(FE_FrameBuffer* frameBuffer, Uint32 posX, Uint32 posY, Uint32 w, Uint32 h)
{
	frameBuffer->h = h;
	frameBuffer->w = w;
	frameBuffer->posX = posX;
	frameBuffer->posY = posY;
}
