#pragma once

void FE_DECL FE_Renderer3DInit();
void FE_DECL FE_Renderer3DShutdown();

void FE_DECL FE_Renderer3DBeginScene(const FE_Camera3D* cam);
void FE_DECL FE_Renderer3DEndScene();

void FE_DECL FE_Renderer3DDraw();
void FE_DECL FE_Renderer3DReset();
void FE_DECL FE_Renderer3DResizeVertexBuffer(SizeT bufferCountToAdd);
void FE_DECL FE_Renderer3DResizeIndexBuffer(SizeT bufferCountToAdd);

Uint32 FE_DECL FE_Renderer3DGetIndexCount();
SizeT FE_DECL FE_Renderer3DGetVertexCount();
SizeT FE_DECL FE_Renderer3DGetVertexBufferCount();

void FE_DECL FE_Renderer3DDrawMesh(const FE_Mesh* mesh); 
void FE_DECL FE_Renderer3DDrawModel(const FE_Model3D* model);