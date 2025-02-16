message("==== VulkanMemoryAllocator build (${CMAKE_BUILD_TYPE}) ====")

add_library("VulkanMemoryAllocator" STATIC
      "FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocator/include/vk_mem_alloc.h"
  "FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocatorCompile.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("VulkanMemoryAllocator"
    "Vulkan"
  )
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    OUTPUT_NAME "VulkanMemoryAllocator"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/VulkanMemoryAllocator"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/VulkanMemoryAllocator"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Debug-windows-x86_64/VulkanMemoryAllocator"
  )
endif()

target_include_directories("VulkanMemoryAllocator" PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/VulkanSDK/1.3.290.0/Include"
)

target_link_libraries("VulkanMemoryAllocator"
  $<$<CONFIG:Debug>:Vulkan>
)
target_compile_options("VulkanMemoryAllocator" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("VulkanMemoryAllocator"
    "Vulkan"
  )
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    OUTPUT_NAME "VulkanMemoryAllocator"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/VulkanMemoryAllocator"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/VulkanMemoryAllocator"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Release-windows-x86_64/VulkanMemoryAllocator"
  )
endif()

target_compile_definitions("VulkanMemoryAllocator" PRIVATE
)
target_link_directories("VulkanMemoryAllocator" PRIVATE
)
target_link_libraries("VulkanMemoryAllocator"
  $<$<CONFIG:Release>:Vulkan>
)

target_compile_options("VulkanMemoryAllocator" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  add_dependencies("VulkanMemoryAllocator"
    "Vulkan"
  )
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    OUTPUT_NAME "VulkanMemoryAllocator"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/VulkanMemoryAllocator"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/VulkanMemoryAllocator"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/VulkanSDK/bin/Dist-windows-x86_64/VulkanMemoryAllocator"
  )
endif()
target_compile_definitions("VulkanMemoryAllocator" PRIVATE
)
target_link_directories("VulkanMemoryAllocator" PRIVATE
)
target_link_libraries("VulkanMemoryAllocator"
  $<$<CONFIG:Dist>:Vulkan>
)

target_compile_options("VulkanMemoryAllocator" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("VulkanMemoryAllocator" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
