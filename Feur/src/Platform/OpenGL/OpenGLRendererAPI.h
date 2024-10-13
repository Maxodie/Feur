#pragma once

Bool FE_API OpenGLInit_impl(RendererAPIData* apiData);
void FE_API OpenGLSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height);
void FE_API OpenGLClearScreenColor_impl();
void FE_API OpenGLClear_impl();
void FE_API OpenGLDrawIndex_impl(); 
void FE_API OpenGLShutdown_impl(RendererAPIData* apiData);