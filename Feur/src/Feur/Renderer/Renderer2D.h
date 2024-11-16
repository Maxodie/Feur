#pragma once

void FE_Renderer2DInit();
void FE_Renderer2DShutdown();

void FE_Renderer2DBeginScene();
void FE_Renderer2DEndScene();

void FE_Renderer2DDraw();
void FE_Renderer2DReset();
void FE_Renderer2DCreateTemporaryBuffer();

//getters
Uint32 FE_Renderer2DGetIndexCount();

//Draw quad
void FE_Renderer2DDrawQuad(const ILDA_vector3f* position, const ILDA_vector2f * size, const FE_Color* color);