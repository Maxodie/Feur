#pragma once

struct FE_Event;

typedef enum { FE_WINDOW_API_SDL, FE_WINDOW_API_GLFW } Window_API_Type;


typedef enum FE_CursorStandardShape
{
	FE_CURSOR_SHAPE_ARROW_CURSOR = 0x00036001,
	FE_CURSOR_SHAPE_IBEAM_CURSOR = 0x00036002,
	FE_CURSOR_SHAPE_CROSSHAIR_CURSOR = 0x00036003,
	FE_CURSOR_SHAPE_HAND_CURSOR = 0x00036004,
	FE_CURSOR_SHAPE_HRESIZE_CURSOR = 0x00036005,
	FE_CURSOR_SHAPE_VRESIZE_CURSOR = 0x00036006,
} FE_CursorStandardShape;

typedef struct WindowData
{
	struct GraphicsContext {
		void* windowHandle;
		void (*Init)(struct WindowData*);
		void (*SwapBuffers)(struct WindowData*);
	}graphicsContext;

	Uint32 w, h;
	ILDA_vector2d windowMousePos;
	void* nativeWindow;
	void* nativeCursor;
	FE_CursorStandardShape pendingCursorShape;
	FE_CursorStandardShape currentCursorShape;
	void (*EventCallback)(struct FE_Event);
	Bool isMinimized;
} WindowData;

typedef struct Window_API
{
	Window_API_Type API_Type;
	Bool (*Init)();
	Bool (*CreateAppWindow)(WindowData*);
	void (*PollEvent)();
	void (*DestroyWindow)(WindowData*);
	void (*Update)(WindowData*);
	void (*SetCursorShape)(WindowData*, FE_CursorStandardShape);
} Window_API;

void FE_DECL InitWindowAPI();
void FE_DECL CreateAppWindow(WindowData* windowData);

const Window_API* FE_DECL GetWindowAPI();
