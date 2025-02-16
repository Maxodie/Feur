#include "fepch.h"
#include "Feur/Renderer/Shader.h"

#include "Feur/Renderer/RenderCommand.h"

void FE_DECL FE_ShaderChangeRenderPipeline(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	RenderCommandChangeGraphicsPipelineShaders(vertexShaderPath, fragmentShaderPath);
}

void FE_DECL FE_UpdateRenderPipeline()
{
	RenderCommandPostTaskUpdateGraphicsPipelineShaders();
}
