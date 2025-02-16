message("==== FeurEngine build (${CMAKE_BUILD_TYPE}) ====")

add_library(FeurEngine STATIC
    FeurEngine/src/Feur.h
        FeurEngine/src/Feur/Core/Application.c
        FeurEngine/src/Feur/Core/Application.h
        FeurEngine/src/Feur/Core/Core.h
        FeurEngine/src/Feur/Core/EntryPoint.h
            FeurEngine/src/Feur/Core/Input/Input.c
            FeurEngine/src/Feur/Core/Input/Input.h
            FeurEngine/src/Feur/Core/Input/KeyCode.h
        FeurEngine/src/Feur/Core/Layer.c
        FeurEngine/src/Feur/Core/Layer.h
        FeurEngine/src/Feur/Core/LayerStack.c
        FeurEngine/src/Feur/Core/LayerStack.h
            FeurEngine/src/Feur/Core/Log/Log.c
            FeurEngine/src/Feur/Core/Log/Log.h
            FeurEngine/src/Feur/Core/Memory/FreeListAllocator.c
            FeurEngine/src/Feur/Core/Memory/FreeListAllocator.h
            FeurEngine/src/Feur/Core/Memory/MemoryAllocator.c
            FeurEngine/src/Feur/Core/Memory/MemoryAllocator.h
            FeurEngine/src/Feur/Core/Memory/PoolAllocator.c
            FeurEngine/src/Feur/Core/Memory/PoolAllocator.h
            FeurEngine/src/Feur/Core/Memory/StackAllocator.c
            FeurEngine/src/Feur/Core/Memory/StackAllocator.h
            FeurEngine/src/Feur/Core/Utils/ByteFlag.c
            FeurEngine/src/Feur/Core/Utils/ByteFlag.h
                FeurEngine/src/Feur/Core/Utils/ECS/ECS.c
                FeurEngine/src/Feur/Core/Utils/ECS/ECS.h
                FeurEngine/src/Feur/Core/Utils/ECS/ECSSystems.c
                FeurEngine/src/Feur/Core/Utils/ECS/ECSSystems.h
            FeurEngine/src/Feur/Core/Utils/FeString.c
            FeurEngine/src/Feur/Core/Utils/FeString.h
            FeurEngine/src/Feur/Core/Utils/FeurSort.c
            FeurEngine/src/Feur/Core/Utils/FeurSort.h
            FeurEngine/src/Feur/Core/Utils/FileSystem.c
            FeurEngine/src/Feur/Core/Utils/FileSystem.h
            FeurEngine/src/Feur/Core/Utils/List.c
            FeurEngine/src/Feur/Core/Utils/List.h
            FeurEngine/src/Feur/Core/Utils/Optional.c
            FeurEngine/src/Feur/Core/Utils/Optional.h
            FeurEngine/src/Feur/Core/Window/Window.c
            FeurEngine/src/Feur/Core/Window/Window.h
        FeurEngine/src/Feur/Debug/Benchmark.c
        FeurEngine/src/Feur/Debug/Benchmark.h
        FeurEngine/src/Feur/Event/Event.c
        FeurEngine/src/Feur/Event/Event.h
        FeurEngine/src/Feur/Nuklear/NuklearLayer.c
        FeurEngine/src/Feur/Nuklear/NuklearLayer.h
        FeurEngine/src/Feur/Renderer/Buffers.c
        FeurEngine/src/Feur/Renderer/Buffers.h
        FeurEngine/src/Feur/Renderer/Camera.c
        FeurEngine/src/Feur/Renderer/Camera.h
        FeurEngine/src/Feur/Renderer/GraphicsContext.c
        FeurEngine/src/Feur/Renderer/GraphicsContext.h
            FeurEngine/src/Feur/Renderer/Models/Helper.c
            FeurEngine/src/Feur/Renderer/Models/Helper.h
            FeurEngine/src/Feur/Renderer/Models/Mesh.c
            FeurEngine/src/Feur/Renderer/Models/Mesh.h
        FeurEngine/src/Feur/Renderer/RenderCommand.c
        FeurEngine/src/Feur/Renderer/RenderCommand.h
        FeurEngine/src/Feur/Renderer/Renderer.c
        FeurEngine/src/Feur/Renderer/Renderer.h
        FeurEngine/src/Feur/Renderer/Renderer2D.c
        FeurEngine/src/Feur/Renderer/Renderer2D.h
        FeurEngine/src/Feur/Renderer/Renderer3D.c
        FeurEngine/src/Feur/Renderer/Renderer3D.h
        FeurEngine/src/Feur/Renderer/RendererAPI.c
        FeurEngine/src/Feur/Renderer/RendererAPI.h
        FeurEngine/src/Feur/Renderer/Shader.c
        FeurEngine/src/Feur/Renderer/Shader.h
        FeurEngine/src/Platform/Nuklear/NuklearGlfwGl4.h
        FeurEngine/src/Platform/Nuklear/NuklearGlfwVulkan.h
        FeurEngine/src/Platform/Nuklear/OpenGLNuklearLayer.c
        FeurEngine/src/Platform/Nuklear/OpenGLNuklearLayer.h
        FeurEngine/src/Platform/Nuklear/VulkanNuklearLayer.c
        FeurEngine/src/Platform/Nuklear/VulkanNuklearLayer.h
        FeurEngine/src/Platform/OpenGL/OpenGLBuffers.c
        FeurEngine/src/Platform/OpenGL/OpenGLBuffers.h
        FeurEngine/src/Platform/OpenGL/OpenGLGraphicsContext.c
        FeurEngine/src/Platform/OpenGL/OpenGLGraphicsContext.h
        FeurEngine/src/Platform/OpenGL/OpenGLRendererAPIimpl.c
        FeurEngine/src/Platform/OpenGL/OpenGLRendererAPIimpl.h
            FeurEngine/src/Platform/Vulkan/Debug/VulkanDebug.c
            FeurEngine/src/Platform/Vulkan/Debug/VulkanDebug.h
            FeurEngine/src/Platform/Vulkan/Debug/VulkanValidationLayer.c
            FeurEngine/src/Platform/Vulkan/Debug/VulkanValidationLayer.h
            FeurEngine/src/Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.c
            FeurEngine/src/Platform/Vulkan/RenderPipeline/VulkanRenderPipeline.h
            FeurEngine/src/Platform/Vulkan/RenderPipeline/VulkanShader.c
            FeurEngine/src/Platform/Vulkan/RenderPipeline/VulkanShader.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanCommands.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanCommands.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanDevice.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanDevice.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanImageView.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanImageView.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanMemoryAllocation.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanMemoryAllocation.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanSetup.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanSetup.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanStructures.h
            FeurEngine/src/Platform/Vulkan/Setup/VulkanSwapChain.c
            FeurEngine/src/Platform/Vulkan/Setup/VulkanSwapChain.h
        FeurEngine/src/Platform/Vulkan/VulkanBuffers.c
        FeurEngine/src/Platform/Vulkan/VulkanBuffers.h
        FeurEngine/src/Platform/Vulkan/VulkanGraphicsContext.c
        FeurEngine/src/Platform/Vulkan/VulkanGraphicsContext.h
        FeurEngine/src/Platform/Vulkan/VulkanRendererAPIimpl.c
        FeurEngine/src/Platform/Vulkan/VulkanRendererAPIimpl.h
            FeurEngine/src/Platform/Window/GLFW/GLFWWindowsInput.c
            FeurEngine/src/Platform/Window/GLFW/GLFWWindowsInput.h
            FeurEngine/src/Platform/Window/GLFW/GLFWWindowsWindow.c
            FeurEngine/src/Platform/Window/GLFW/GLFWWindowsWindow.h
            FeurEngine/src/Platform/Window/SDL/SDLWindowsInput.c
            FeurEngine/src/Platform/Window/SDL/SDLWindowsInput.h
            FeurEngine/src/Platform/Window/SDL/SDLWindowsWindow.c
            FeurEngine/src/Platform/Window/SDL/SDLWindowsWindow.h
    FeurEngine/src/fepch.c
    FeurEngine/src/fepch.h
)

target_link_libraries( FeurEngine PUBLIC
    Glad
    GLFW
    Mathilda
    Vulkan
    VulkanMemoryAllocator
    assimp
    Nuklear
)

set_target_properties(FeurEngine PROPERTIES
    OUTPUT_NAME FeurEngine
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/FeurEngine"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/FeurEngine"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/FeurEngine"
)

target_include_directories(FeurEngine PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/Glad/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocator/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/glfw/GLFW/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/nuklear"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/assimp/assimp/include"
)

target_compile_definitions(FeurEngine PRIVATE
  $<$<CONFIG:Debug>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Debug>:_CRT_SECURE_NO_WARNINGS>
  $<$<CONFIG:Debug>:FE_RENDER_SELECTED_API_VULKAN>
  $<$<CONFIG:Debug>:FE_PLATFORM_WINDOWS>
  $<$<CONFIG:Debug>:FE_DEBUG>
  $<$<CONFIG:Debug>:FE_ENABLE_ASSERTS>


  $<$<CONFIG:Release>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Release>:_CRT_SECURE_NO_WARNINGS>
  $<$<CONFIG:Release>:FE_RENDER_SELECTED_API_VULKAN>
  $<$<CONFIG:Release>:FE_PLATFORM_WINDOWS>
  $<$<CONFIG:Release>:FE_RELEASE>
  $<$<CONFIG:Release>:FE_ENABLE_ASSERTS>


  $<$<CONFIG:Dist>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Dist>:_CRT_SECURE_NO_WARNINGS>
  $<$<CONFIG:Dist>:FE_RENDER_SELECTED_API_VULKAN>
  $<$<CONFIG:Dist>:FE_PLATFORM_WINDOWS>
  $<$<CONFIG:Dist>:FE_DIST>
)

target_precompile_headers(FeurEngine PUBLIC FeurEngine/src/fepch.h)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set_target_properties(FeurEngine PROPERTIES COMPILE_FLAGS "-Wall -Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla ")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties(FeurEngine PROPERTIES COMPILE_FLAGS "-Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla ")
elseif(CMAKE_BUILD_TYPE STREQUAL Dist)
    set_target_properties(FeurEngine PROPERTIES COMPILE_FLAGS "-o3 -Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla ")
endif()

target_compile_options(FeurEngine PRIVATE
  -std=c17

  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>


  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>


  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O3>
)
