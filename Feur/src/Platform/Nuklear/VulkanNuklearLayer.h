#pragma once

void FE_DECL Vulkan_GLFW_NuklearGUIEvent_impl(FE_Event* event);
void FE_DECL Vulkan_GLFW_NuklearGUIBeginRender_impl(NuklearGUIInterface* interface);
void FE_DECL Vulkan_GLFW_NuklearGUIEndRender_impl(NuklearGUIInterface* interface);
void FE_DECL Vulkan_GLFW_NuklearGUIInit_impl(NuklearGUIInterface* interface);
void FE_DECL Vulkan_GLFW_NuklearGUIShutdown_impl(); 

void FE_DECL Vulkan_GLFW_NuklearGUIOnWindowResize_impl(Uint32 width, Uint32 height);