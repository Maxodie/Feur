message("==== Vulkan build (${CMAKE_BUILD_TYPE}) ====")

add_library("Vulkan" STATIC
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/dxc/WinAdapter.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/dxc/dxcapi.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Include/ResourceLimits.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Include/glslang_c_interface.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Include/glslang_c_shader_types.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/MachineIndependent/Versions.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Public/ResourceLimits.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Public/ShaderLang.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/Public/resource_limits_c.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/SPIRV/GlslangToSpv.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/SPIRV/Logger.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/SPIRV/SPVRemapper.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/SPIRV/disassemble.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/glslang/build_info.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/shaderc/env.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/shaderc/shaderc.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/shaderc/status.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/shaderc/visibility.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/AMD_gcn_shader.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/AMD_shader_ballot.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/AMD_shader_explicit_vertex_parameter.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/AMD_shader_trinary_minmax.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/DebugInfo.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/GLSL.std.450.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/NonSemanticClspvReflection.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/NonSemanticDebugBreak.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/NonSemanticDebugPrintf.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/NonSemanticShaderDebugInfo100.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/NonSemanticVkspReflection.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/OpenCL.std.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/OpenCLDebugInfo100.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-headers/spirv.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv-tools/libspirv.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv_cross/GLSL.std.450.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv_cross/spirv.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/spirv_cross/spirv_cross_c.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_av1std.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_av1std_decode.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h264std.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h264std_decode.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h264std_encode.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h265std.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h265std_decode.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codec_h265std_encode.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vk_video/vulkan_video_codecs_common.h
        FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/utility/vk_format_utils.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vk_enum_string_helper.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vk_icd.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vk_layer.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vk_platform.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_android.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_beta.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_core.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_directfb.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_fuchsia.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_ggp.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_ios.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_macos.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_metal.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_screen.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_vi.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_wayland.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_win32.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_xcb.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_xlib.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Include/vulkan/vulkan_xlib_xrandr.h
          FeurEngine/vendor/VulkanSDK/1.3.290.0/Source/SPIRV-Reflect/include/spirv/unified1/spirv.h
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Source/SPIRV-Reflect/spirv_reflect.c
    FeurEngine/vendor/VulkanSDK/1.3.290.0/Source/SPIRV-Reflect/spirv_reflect.h
)

set_target_properties("Vulkan" PROPERTIES
    OUTPUT_NAME "Vulkan"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/Vulkan"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/Vulkan"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/Vulkan"
)

target_include_directories("Vulkan" PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Include"
)

target_compile_definitions("Vulkan" PRIVATE
    $<$<CONFIG:Debug>:_CRT_SECURE_NO_WARNINGS>
    $<$<CONFIG:Debug>:WIN32>
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Debug>:_WINDOWS>
)

target_link_libraries("Vulkan"
    "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/vulkan-1.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/shaderc_shared.lib"
)
target_compile_options("Vulkan" PRIVATE
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-ffast-math>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O2>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-Wall>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-Wextra>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-ffast-math>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O2>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-Wall>
    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-Wextra>


    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-ffast-math>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-Wall>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-Wextra>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-ffast-math>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-Wall>
    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-Wextra>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
set_target_properties("Vulkan" PROPERTIES
    OUTPUT_NAME "Vulkan"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/Vulkan"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/Vulkan"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/Vulkan"
)
endif()
target_include_directories("Vulkan" PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/vulkan/1.3.290.0/Include"
)
target_compile_definitions("Vulkan" PRIVATE
  $<$<CONFIG:Release>:_CRT_SECURE_NO_WARNINGS>
  $<$<CONFIG:Release>:WIN32>
  $<$<CONFIG:Release>:NDEBUG>
  $<$<CONFIG:Release>:PROFILE>
  $<$<CONFIG:Release>:_WINDOWS>
)
target_link_directories("Vulkan" PRIVATE
)
target_link_libraries("Vulkan"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/vulkan-1.lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/shaderc_shared.lib"
)
target_compile_options("Vulkan" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-ffast-math>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-Wall>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-Wextra>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-ffast-math>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-Wall>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-Wextra>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Vulkan" PROPERTIES
    OUTPUT_NAME "Vulkan"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/Vulkan"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/Vulkan"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/Vulkan"
  )
endif()
target_include_directories("Vulkan" PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Include"
)
target_compile_definitions("Vulkan" PRIVATE
  $<$<CONFIG:Dist>:_CRT_SECURE_NO_WARNINGS>
)
target_link_directories("Vulkan" PRIVATE
)
target_link_libraries("Vulkan"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/vulkan-1.lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Lib/shaderc_shared.lib"
)
target_compile_options("Vulkan" PRIVATE
)
