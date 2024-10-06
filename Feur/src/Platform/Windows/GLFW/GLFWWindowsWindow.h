#pragma once

BOOL FE_API CreateGLFWWindow_impl(WindowData* windowData);
void FE_API GLFWDestroyWindow_impl(WindowData* windowData);
void FE_API GLFWPollEvent_impl();
void FE_API GLFWUpdate_impl(WindowData* windowData);