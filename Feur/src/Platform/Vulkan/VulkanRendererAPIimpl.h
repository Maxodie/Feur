#pragma once

Bool VulkanInit_impl(RendererAPIData* apiData);

void VulkanFramePrepare_impl();
Bool VulkanFrameCommandListBegin_impl();
void VulkanBeginRendering_impl(ILDA_vector4f* clearColor);
void VulkanSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height, Uint32 minDepth, Uint32 maxDepth);
void VulkanSetScissor_impl(Uint32 width, Uint32 height);
void VulkanBindPipeline_impl();
void VulkanDrawIndex_impl();
void VulkanEndRendering_impl();
Bool VulkanFrameCommandListEnd_impl();
Bool VulkanFrameSubmit_impl();
Bool VulkanFramePresent_impl();
void VulkanWaitIdle_impl();
void VulkanShutdown_impl();

void VulkanOnWindowResized_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height);

Bool CanVulkanContinueRendering();