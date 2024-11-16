#include "fepch.h"
#include "Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.h"
#include "Platform/Vulkan/Setup/VulkanSetup.h"
#include "Platform/Vulkan/VulkanBuffers.h"

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

	/*---------------------- Vertex Input / BInding ----------------------*/

	VulkanCreateDescriptorSetLayout(vkInfo);

	VkVertexInputBindingDescription bindingDescription = {
		.binding = 0,
		.stride = sizeof(FE_Vertex3D),
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
	};

	// vertex Input
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

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 1,
		.pVertexBindingDescriptions = &bindingDescription, // Optionnal
		.vertexAttributeDescriptionCount = sizeof(attributeDescription) / sizeof(VkVertexInputAttributeDescription),
		.pVertexAttributeDescriptions = attributeDescription
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
		//.polygonMode = VK_POLYGON_MODE_LINE,
		.lineWidth = 1.0f,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_CLOCKWISE, //VK_FRONT_FACE_COUNTER_CLOCKWISE
		//.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
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
		.setLayoutCount = 1,
		.pSetLayouts = &vkInfo->descriptor.setLayout,
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

void VulkanDestoryGraphicsPipeline(FE_VulkanInfo* vkInfo)
{
	vkDestroyPipeline(vkInfo->logicalDevice, vkInfo->graphicsPipeline.handle, NULL);
	vkDestroyPipelineLayout(vkInfo->logicalDevice, vkInfo->graphicsPipeline.layout, NULL);
	VulkanDestroyDescriptionSetLayout(vkInfo);

	VulkanDestroyShaderCompiler(vkInfo);
}

void VulkanGraphicsPipelineBind(VkCommandBuffer cmdBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
	vkCmdBindPipeline(cmdBuffer, pipelineBindPoint, pipeline);
}

void VulkanCreateDescriptorSetLayout(FE_VulkanInfo* vkInfo)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {
		.binding = 0,
		.descriptorCount = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.pImmutableSamplers = VK_NULL_HANDLE,
		.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
	};

	VkDescriptorSetLayoutCreateInfo layoutInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = 1,
		.pBindings = &uboLayoutBinding,
	};

	VkResult result = vkCreateDescriptorSetLayout(vkInfo->logicalDevice, &layoutInfo, NULL, &vkInfo->descriptor.setLayout);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create vulkan DescriptorSetLayout : %d", result);
}

void VulkanDestroyDescriptionSetLayout(FE_VulkanInfo* vkInfo)
{
	vkDestroyDescriptorSetLayout(vkInfo->logicalDevice, vkInfo->descriptor.setLayout, NULL);
}

void VulkanCreateDescriptorPool(FE_VulkanInfo* vkInfo)
{
	VkDescriptorPoolSize poolSize = {
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = vkInfo->swapChain.maxFramesInFlight,
	};

	VkDescriptorPoolCreateInfo poolInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.poolSizeCount = 1,
		.pPoolSizes = &poolSize,
		.maxSets = vkInfo->swapChain.maxFramesInFlight,
		.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
	};

	// TODO : change this for vmaCreatePool()
	VkResult result = vkCreateDescriptorPool(vkInfo->logicalDevice, &poolInfo, NULL, &vkInfo->descriptor.pool);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to create vulkan descriptor pool : %d", result);
}

void VulkanDestroyDescriptorPool(FE_VulkanInfo* vkInfo)
{
	vkDestroyDescriptorPool(vkInfo->logicalDevice, vkInfo->descriptor.pool, NULL);
}

void VulkanCreateDescriptorSets(FE_VulkanInfo* vkInfo)
{
	VkDescriptorSetLayout* layouts = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * sizeof(VkDescriptorSetLayout));
	for (SizeT i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++)
	{
		layouts[i] = vkInfo->descriptor.setLayout;
	}

	VkDescriptorSetAllocateInfo allocInfo = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.pool = vkInfo->descriptor.pool,
		.descriptorSetCount = vkInfo->swapChain.maxFramesInFlight,
		.pSetLayouts = layouts,
	};

	vkInfo->descriptor.sets = FE_MemoryGeneralAlloc(vkInfo->swapChain.maxFramesInFlight * sizeof(VkDescriptorSet));

	VkResult result = vkAllocateDescriptorSets(vkInfo->logicalDevice, &allocInfo, vkInfo->descriptor.sets);
	FE_CORE_ASSERT(result == VK_SUCCESS, "failed to  allocate descriptor sets : %d", result);

	for (size_t i = 0; i < vkInfo->swapChain.maxFramesInFlight; i++) {
		VkDescriptorBufferInfo bufferInfo = {
			.buffer = vkInfo->uniformData.uniformBuffers[i].buffer,
			.offset = 0,
			.range = sizeof(FE_UniformBufferObject),
		};

		VkWriteDescriptorSet descriptorWrite = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = vkInfo->descriptor.sets[i],
			.dstBinding = 0,
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.pBufferInfo = &bufferInfo,
			.pImageInfo = NULL, //optional
			.pTexelBufferView = NULL, //optional
		};

		vkUpdateDescriptorSets(vkInfo->logicalDevice, 1, &descriptorWrite, 0, NULL);
	}

	FE_MemoryGeneralFree(layouts);
}

void VulkanDestroyDescriptorSets(FE_VulkanInfo* vkInfo)
{
	//vkFreeDescriptorSets(vkInfo->logicalDevice, vkInfo->descriptor.pool, vkInfo->swapChain.maxFramesInFlight, vkInfo->descriptor.sets);
	FE_MemoryGeneralFree(vkInfo->descriptor.sets);
}
