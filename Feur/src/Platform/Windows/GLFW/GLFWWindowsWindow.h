#pragma once

BOOL CreateGLFWWindow_impl(WindowData* windowData);
void GLFWDestroyWindow_impl(WindowData* windowData);
void GLFWPollEvent_impl();
void GLFWUpdate_impl(WindowData* windowData);