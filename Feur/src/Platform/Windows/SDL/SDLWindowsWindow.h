#pragma once

BOOL FE_API CreateSDLWindow_impl(WindowData* windowData);
void FE_API SDLDestroyWindow_impl(WindowData* windowData);
void FE_API SDLPollEvent_impl();