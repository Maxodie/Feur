#pragma once

BOOL FE_API VulkanInit_impl(RendererAPIData* apiData);

void FE_API VulkanSetViewport_impl(Uint32 x, Uint32 y, Uint32 width, Uint32 height);
void FE_API VulkanClearScreenColor_impl();
void FE_API VulkanClear_impl();
void FE_API VulkanDrawIndex_impl();
void FE_API VulkanShutdown_impl(RendererAPIData* apiData);