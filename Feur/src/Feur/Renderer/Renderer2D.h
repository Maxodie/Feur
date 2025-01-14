#pragma once

void FE_DECL FE_Renderer2DInit();
void FE_DECL FE_Renderer2DShutdown();

void FE_DECL FE_Renderer2DBeginScene(const FE_Camera3D* cam);
void FE_DECL FE_Renderer2DEndScene();

void FE_DECL FE_Renderer2DDraw();
void FE_DECL FE_Renderer2DReset();
void FE_DECL FE_Renderer2DResizeBuffer(SizeT bufferCountToAdd);

//getters
Uint32 FE_DECL FE_Renderer2DGetIndexCount();
SizeT FE_DECL FE_Renderer2DGetVertexCount();
SizeT FE_DECL FE_Renderer2DGetVertexBufferCount();

//Draw quad
void FE_DECL FE_Renderer2DDrawQuad(const ILDA_vector3f* position, const ILDA_vector2f * size, const FE_Color* color);