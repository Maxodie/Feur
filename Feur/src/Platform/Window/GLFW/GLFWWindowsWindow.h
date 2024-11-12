#pragma once

Bool FE_DECL CreateGLFWInit_impl(WindowData* windowData);
Bool FE_DECL CreateGLFWWindow_impl(WindowData* windowData);
void FE_DECL GLFWDestroyWindow_impl(WindowData* windowData);
void FE_DECL GLFWPollEvent_impl();
void FE_DECL GLFWUpdate_impl(WindowData* windowData);