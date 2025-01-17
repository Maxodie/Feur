#pragma once

typedef struct NuklearGUIInterface
{
	void (*Init)(struct NuklearGUIInterface* interface);
	void (*OnEvent)(FE_Event*);
	void (*OnBeginRender)(struct NuklearGUIInterface* interface);
	void (*OnEndRender)(struct NuklearGUIInterface* interface);
	void (*Shutdown)();

	void (*OnWindowResize)(Uint32 width, Uint32 height);

	void* handle;

} NuklearGUIInterface;

void FE_DECL NuklearGUIInterfaceInit(NuklearGUIInterface* interface); 
void FE_DECL NuklearGUIBeginRender(); 
void FE_DECL NuklearGUIEndRender();