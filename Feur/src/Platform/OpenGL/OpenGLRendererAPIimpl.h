#pragma once

Bool OpenGLInit_impl(RendererAPIData* apiData);
void OpenGLOnWindowResize_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 drawIndexCount);
void OpenGLBeginRendering_impl(ILDA_vector4f * clearColor);
void OpenGLDrawIndex_impl(Uint32 indexCount); 
void OpenGLShutdown_impl();