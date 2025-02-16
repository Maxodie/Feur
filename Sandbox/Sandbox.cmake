message("==== Sandbox build (${CMAKE_BUILD_TYPE}) ====")

add_executable(Sandbox
    Sandbox/src/sandbox.c
    Sandbox/src/sandboxOpenGLTest.c
)

target_link_libraries(Sandbox PUBLIC
    FeurEngine
)

set_target_properties(Sandbox PROPERTIES
    OUTPUT_NAME Sandbox
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Sandbox"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Sandbox"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Sandbox"
  )

target_include_directories(Sandbox PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/src"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/nuklear"
  "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/Glad/include"
)

target_compile_definitions(Sandbox PRIVATE
    $<$<CONFIG:Debug>:ILDA_HAVE_INLINE>
    $<$<CONFIG:Debug>:_FEUR_TEST_VULKAN_SANDBOX_>
    $<$<CONFIG:Debug>:FE_PLATFORM_WINDOWS>
    $<$<CONFIG:Debug>:FE_DEBUG>
    $<$<CONFIG:Debug>:FE_ENABLE_ASSERTS>


    $<$<CONFIG:Release>:ILDA_HAVE_INLINE>
    $<$<CONFIG:Release>:_FEUR_TEST_VULKAN_SANDBOX_>
    $<$<CONFIG:Release>:FE_PLATFORM_WINDOWS>
    $<$<CONFIG:Release>:FE_RELEASE>
    $<$<CONFIG:Release>:FE_ENABLE_ASSERTS>


    $<$<CONFIG:Dist>:ILDA_HAVE_INLINE>
    $<$<CONFIG:Dist>:_FEUR_TEST_VULKAN_SANDBOX_>
    $<$<CONFIG:Dist>:FE_PLATFORM_WINDOWS>
    $<$<CONFIG:Dist>:FE_DIST>
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set_target_properties(Sandbox PROPERTIES COMPILE_FLAGS "-Wall -Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties(Sandbox PROPERTIES COMPILE_FLAGS "-Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla")
elseif(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties(Sandbox PROPERTIES COMPILE_FLAGS "-Wno-incompatible-pointer-types-discards-qualifiers -Wno-incompatible-function-pointer-types -Wno-vla")
endif()

target_compile_options(Sandbox PRIVATE
  -std=c17
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>


  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>


  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O3>
)
