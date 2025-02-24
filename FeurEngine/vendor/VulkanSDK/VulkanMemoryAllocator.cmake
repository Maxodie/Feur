message("==== VulkanMemoryAllocator build (${CMAKE_BUILD_TYPE}) ====")

add_library(VulkanMemoryAllocator STATIC
        FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocator/include/vk_mem_alloc.h
    FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocatorCompile.cpp
)

add_dependencies(VulkanMemoryAllocator
    Vulkan
)

set_target_properties(VulkanMemoryAllocator PROPERTIES
    OUTPUT_NAME VulkanMemoryAllocator
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/VulkanMemoryAllocator"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/VulkanMemoryAllocator"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/VulkanMemoryAllocator"
)

target_include_directories(VulkanMemoryAllocator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Include"
)

target_link_libraries(VulkanMemoryAllocator
    Vulkan
)

target_compile_options(VulkanMemoryAllocator PRIVATE
    -m64


  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>


  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>


  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)

set_target_properties(VulkanMemoryAllocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
)
