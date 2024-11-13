#include "fepch.h"
#include "Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"

#include "Platform/Vulkan/RenderPipeline/VulkanShader.h"

void VulkanCreateGraphicsPipeline(FE_VulkanInfo* vkInfo)
{
	VulkanCreateShaderCompiler(vkInfo);

	VkShaderModule vertexShader = VulkanCreateShaderModule(vkInfo, "VertexShader", VERTEX_SHADER);
	VkShaderModule fragmentShader = VulkanCreateShaderModule(vkInfo, "FragmentShader", FRAGMENT_SHADER);

	/*---------------------- Shader Stage Creation ----------------------*/

	VkPipelineShaderStageCreateInfo vertexShaderCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = vertexShader,
		.pName = "main"
	};

	VkPipelineShaderStageCreateInfo fragmentShaderCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = fragmentShader,
		.pName = "main"
	};

	VkPipelineShaderStageCreateInfo shaderStages[2] = { vertexShaderCreateInfo, fragmentShaderCreateInfo };

	/*---------------------- Dynamic State ----------------------*/

	VkDynamicState dynamicStates[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = sizeof(dynamicStates) / sizeof(VkDynamicState),
		.pDynamicStates = dynamicStates

	};

	/*---------------------- Vertex Input ----------------------*/

	// vertex bindings
	VkVertexInputBindingDescription bindingDescription = {
		.binding = 0,
		.stride = sizeof(FE_Vertex3D),
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
	};

	/*FE_List(VkVertexInputAttributeDescription) attributeDescription = { 0 };
	FE_ListInit(attributeDescription);
	FE_ListResize(attributeDescription, 2);*/
	VkVertexInputAttributeDescription attributeDescription[2] = {
		(VkVertexInputAttributeDescription) {
			.binding = 0,
			.location = 0,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = offsetof(FE_Vertex3D, position)
		},
		(VkVertexInputAttributeDescription) {
			.binding = 0,
			.location = 1,
			.format = VK_FORMAT_R32G32B32A32_SFLOAT,
			.offset = offsetof(FE_Vertex3D, color)
		}
	
	};

	VkPipelineVertexInputStateCreateInfo  vertexInputInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 1,
		.pVertexBindingDescriptions = &bindingDescription, // Optionnal
		.vertexAttributeDescriptionCount = sizeof(attributeDescription) / sizeof(VkVertexInputAttributeDescription),
		.pVertexAttributeDescriptions = attributeDescription

		//FIXME: remove once we have our vertex buffers
		//.vertexBindingDescriptionCount = 0,
		//.pVertexBindingDescriptions = VK_NULL_HANDLE, // Optionnal
		//.vertexAttributeDescriptionCount = 0,
		//.pVertexAttributeDescriptions = VK_NULL_HANDLE
	};
	
	/*---------------------- Input Assembly ----------------------*/

	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE
	};

	VkPipelineViewportStateCreateInfo viewportState = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.scissorCount = 1,
	};

	/*---------------------- Rasterize ----------------------*/

	VkPipelineRasterizationStateCreateInfo rasterizer = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.lineWidth = 1.0f,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 0.0f, // Optionnal
		.depthBiasClamp = 0.0f, // Optionnal
		.depthBiasSlopeFactor = 0.0f // Optionnal
	};

	/*---------------------- Multisampling ----------------------*/

	VkPipelineMultisampleStateCreateInfo multisampling = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.sampleShadingEnable = VK_FALSE,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.minSampleShading = 1.0f, // Optionnal
		.pSampleMask = NULL, // Optionnal
		.alphaToCoverageEnable = VK_FALSE, // Optionnal
		.alphaToOneEnable = VK_FALSE // Optionnal
	};
	/*---------------------- Color Blending ----------------------*/

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_ONE, // Optionnal
		.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO, // Optionnal
		.colorBlendOp = VK_BLEND_OP_ADD, // Optionnal
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, // Optionnal
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO, // Optionnal
		.alphaBlendOp = VK_BLEND_OP_ADD // Optionnal
	};

	VkPipelineColorBlendStateCreateInfo colorBlending = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY, // Optionnal
		.attachmentCount = 1,
		.pAttachments = &colorBlendAttachment,
		.blendConstants[0] = 0.0f, // Optionnal
		.blendConstants[1] = 0.0f, // Optionnal
		.blendConstants[2] = 0.0f, // Optionnal
		.blendConstants[3] = 0.0f // Optionnal
	};

	/*---------------------- Pipeline Layout ----------------------*/

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 0,            // Optionnal
		.pSetLayouts = NULL,         // Optionnal
		.pushConstantRangeCount = 0,    // Optionnal
		.pPushConstantRanges = NULL // Optionnal
	};

	VkResult result = vkCreatePipelineLayout(vkInfo->logicalDevice, &pipelineLayoutInfo, NULL, &vkInfo->graphicsPipeline.layout);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create vulkan pipeline layout - %d", result);

	/*---------------------- Graphics Pipeline ----------------------*/

	VkGraphicsPipelineCreateInfo pipelineInfo = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2,
		.pStages = shaderStages,
		.pVertexInputState = &vertexInputInfo,
		.pInputAssemblyState = &inputAssembly,
		.pViewportState = &viewportState,
		.pRasterizationState = &rasterizer,
		.pMultisampleState = &multisampling,
		.pDepthStencilState = NULL, // Optionnal
		.pColorBlendState = &colorBlending,
		.pDynamicState = &dynamicState,
		.layout = vkInfo->graphicsPipeline.layout,
		.renderPass = VK_NULL_HANDLE,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE, // Optionnal
		.basePipelineIndex = -1, // Optionnal
	};

	VkPipelineRenderingCreateInfo pipelineRenderingCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
		.colorAttachmentCount = 1,
		.pColorAttachmentFormats = &vkInfo->swapChain.imageFormat,
		.depthAttachmentFormat = VK_FORMAT_UNDEFINED,
		.stencilAttachmentFormat = VK_FORMAT_UNDEFINED,
		.pNext = VK_NULL_HANDLE,
	};

	pipelineInfo.pNext = &pipelineRenderingCreateInfo;

	result = vkCreateGraphicsPipelines(vkInfo->logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &vkInfo->graphicsPipeline.handle);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create vulkan graphics pipeline");

	// cleanup shader modules
	vkDestroyShaderModule(vkInfo->logicalDevice, fragmentShader, NULL);
	vkDestroyShaderModule(vkInfo->logicalDevice, vertexShader, NULL);
}

void VulkanCleanupGraphicsPipeline(FE_VulkanInfo* vkInfo)
{
	vkDestroyPipeline(vkInfo->logicalDevice, vkInfo->graphicsPipeline.handle, NULL);
	vkDestroyPipelineLayout(vkInfo->logicalDevice, vkInfo->graphicsPipeline.layout, NULL);
	
	VulkanDestroyShaderCompiler(vkInfo);
}

void VulkanGraphicsPipelineBind(VkCommandBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
	vkCmdBindPipeline(cmdBuffer, pipelineBindPoint, pipeline);
}
