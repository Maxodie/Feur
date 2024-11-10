#pragma once

Bool OpenGLInit_impl(RendererAPIData* apiData);
void OpenGLOnWindowResize_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
void OpenGLBeginRendering_impl(ILDA_vector4f * clearColor);
void OpenGLDrawIndex_impl(); 
void OpenGLShutdown_impl();