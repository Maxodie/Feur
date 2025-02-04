#include "fepch.h"
#include "Platform/Vulkan/RenderPipeline/VulkanShader.h"

#include "Platform/Vulkan/Setup/VulkanSetup.h"

void VulkanCreateShaderCompiler(FE_VulkanInfo* vkInfo)
{
	vkInfo->shaderCompiler = shaderc_compiler_initialize();
}

void VulkanDestroyShaderCompiler(FE_VulkanInfo* vkInfo)
{
	shaderc_compiler_release(vkInfo->shaderCompiler);
}

VkShaderModule VulkanCreateShaderModule(FE_VulkanInfo* vkInfo, const char* shaderName, FE_VulkanShaderKind kind)
{
	FE_CORE_LOG_DEBUG("%s shader file", shaderName);

	FE_File file;
	if (!FE_FileSystemOpen(shaderName, FILE_MODE_READ_BINARY, &file))
	{
		FE_CORE_LOG_ERROR("failed to open shader file : %s", shaderName);
		return VK_NULL_HANDLE;
	}


	//read entire file
	SizeT size;
	FE_FileSystemGetSize(&file, &size);
	Byte* fileBuffer = FE_MemoryGeneralAlloc(sizeof(Byte) * size);
	SizeT readSize;
	if(!FE_FileSystemReadAllBytes(&file, fileBuffer, &readSize))
	{
		FE_MemoryGeneralFree(fileBuffer);
		FE_FileSystemClose(&file);
		FE_CORE_LOG_ERROR("failed to read all the bytes from shader file : %s", shaderName);
		return VK_NULL_HANDLE;
	}

	//compile shader to Spir-v at Runtime

	shaderc_shader_kind shaderKind;

	switch (kind)
	{
	case VERTEX_SHADER:
		shaderKind = shaderc_glsl_vertex_shader;
		break;
	case FRAGMENT_SHADER:
		shaderKind = shaderc_glsl_fragment_shader;
		break;
	default:
		FE_MemoryGeneralFree(fileBuffer);
		FE_FileSystemClose(&file);
		FE_CORE_LOG_ERROR("failed to load shader kind for the shader : %s", shaderName);
		return VK_NULL_HANDLE;
		break;
	}

	shaderc_compilation_result_t shaderCompilerResult = shaderc_compile_into_spv(
		vkInfo->shaderCompiler, (const char*)fileBuffer, readSize, shaderKind, shaderName, "main", NULL
	);

	FE_MemoryGeneralFree(fileBuffer);
	FE_FileSystemClose(&file);

	if (shaderCompilerResult == NULL)
	{
		FE_CORE_LOG_ERROR("failed to compile the shader file : %s to SPIR-V", shaderName);
		return VK_NULL_HANDLE;
	}

	//compile shader
	shaderc_compilation_status status = shaderc_result_get_compilation_status(shaderCompilerResult);

	if (status != shaderc_compilation_status_success)
	{
		const char* errorMsg = shaderc_result_get_error_message(shaderCompilerResult);
		SizeT errorCount = shaderc_result_get_num_errors(shaderCompilerResult);
		FE_CORE_LOG_ERROR("Error compiling shader with %zu error(s) and warning(s) :\n%s", errorCount, errorMsg);
		shaderc_result_release(shaderCompilerResult);

		return VK_NULL_HANDLE;
	}

	//successfull compile
	switch (kind)
	{
	case VERTEX_SHADER:
		FE_CORE_LOG_SUCCESS("Vertex shader compile successfully");
		break;
	case FRAGMENT_SHADER:
		FE_CORE_LOG_SUCCESS("Vertex shader compile successfully");
		break;
	default:
		FE_CORE_LOG_SUCCESS("Unknown shader type compile successfully");
		break;
	}

	//check for warnings
	SizeT warningcount = shaderc_result_get_num_warnings(shaderCompilerResult);
	if (warningcount)
	{
		const char* warningMsg = shaderc_result_get_error_message(shaderCompilerResult);
		FE_CORE_LOG_WARNING("%zu warnings were generated during shader compilation :\n%s", warningcount, warningMsg);
	}

	//get code from result and release result
	const Byte* bytes = shaderc_result_get_bytes(shaderCompilerResult);
	SizeT resultSize = shaderc_result_get_length(shaderCompilerResult);

	Uint32* code = FE_MemoryGeneralAlloc(resultSize);
	memcpy(code, bytes, resultSize);

	shaderc_result_release(shaderCompilerResult);

	//create vulkan shader module
	VkShaderModuleCreateInfo createInfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = resultSize,
		.pCode = code
	};

	VkShaderModule shaderModule;
	VkResult result = vkCreateShaderModule(vkInfo->logicalDevice, &createInfo, NULL, &shaderModule);
	
	FE_MemoryGeneralFree(code);

#ifndef FE_DIST
	if (result != VK_SUCCESS)
	{
		FE_CORE_LOG_ERROR("failed to create vulkan shaderModule with result : %d", result);
		return VK_NULL_HANDLE;
	}
#endif
	
	return shaderModule;
}
