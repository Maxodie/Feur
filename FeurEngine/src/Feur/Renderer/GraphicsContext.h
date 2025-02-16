#pragma once



//the graphics context must be in the window data to avoid problem with raw ptr, destruction and nerd stuff
/*typedef struct GraphicsContext
{
	void* windowHandle;
	void (*Init)(struct WindowData*);
	void (*SwapBuffers)(struct WindowData*);
} GraphicsContext;
*/
void FE_DECL InitWindowCreationHintParameters();
void FE_DECL CreateGraphicsContext(struct WindowData* WindowData);