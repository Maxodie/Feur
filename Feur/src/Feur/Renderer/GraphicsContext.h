#pragma once



//the graphics context must be in the window data to avoid problem with raw ptr, destruction and nerd stuff
/*typedef struct GraphicsContext
{
	void* windowHandle;
	void (*Init)(struct WindowData*);
	void (*SwapBuffers)(struct WindowData*);
} GraphicsContext;
*/
void CreateGraphicsContext(struct WindowData* WindowData);