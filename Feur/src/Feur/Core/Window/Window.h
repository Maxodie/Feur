#pragma once

typedef enum { FE_WINDOW_API_SDL, FE_WINDOW_API_GLFW } Window_API_Type;

typedef struct WindowData
{
	struct GraphicsContext {
		void* windowHandle;
		void (*Init)(struct WindowData*);
		void (*SwapBuffers)(struct WindowData*);
	}graphicsContext;

	int w, h;
	void* nativeWindow;
	void (*EventCallback)(FE_Event);
	Bool isMinimized;
} WindowData;

typedef struct Window_API
{
	Window_API_Type API_Type;
	Bool (*CreateAppWindow)(WindowData*);
	void (*PollEvent)();
	void (*DestroyWindow)(WindowData*);
	void (*Update)(WindowData*);
} Window_API;

void FE_API InitWindowAPI();
void FE_API CreateAppWindow(WindowData* windowData);

Window_API* FE_API GetWindowAPI();