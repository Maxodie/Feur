message("==== GLFW3 build (${CMAKE_BUILD_TYPE}) ====")

add_library("GLFW" STATIC
      "FeurEngine/vendor/glfw/GLFW/include/GLFW/glfw3.h"
      "FeurEngine/vendor/glfw/GLFW/include/GLFW/glfw3native.h"
    "FeurEngine/vendor/glfw/GLFW/src/context.c"
    "FeurEngine/vendor/glfw/GLFW/src/egl_context.c"
    "FeurEngine/vendor/glfw/GLFW/src/init.c"
    "FeurEngine/vendor/glfw/GLFW/src/input.c"
    "FeurEngine/vendor/glfw/GLFW/src/internal.h"
    "FeurEngine/vendor/glfw/GLFW/src/mappings.h"
    "FeurEngine/vendor/glfw/GLFW/src/monitor.c"
    "FeurEngine/vendor/glfw/GLFW/src/null_init.c"
    "FeurEngine/vendor/glfw/GLFW/src/null_joystick.c"
    "FeurEngine/vendor/glfw/GLFW/src/null_joystick.h"
    "FeurEngine/vendor/glfw/GLFW/src/null_monitor.c"
    "FeurEngine/vendor/glfw/GLFW/src/null_platform.h"
    "FeurEngine/vendor/glfw/GLFW/src/null_window.c"
    "FeurEngine/vendor/glfw/GLFW/src/osmesa_context.c"
    "FeurEngine/vendor/glfw/GLFW/src/platform.c"
    "FeurEngine/vendor/glfw/GLFW/src/platform.h"
    "FeurEngine/vendor/glfw/GLFW/src/vulkan.c"
    "FeurEngine/vendor/glfw/GLFW/src/wgl_context.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_init.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_joystick.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_module.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_monitor.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_platform.h"
    "FeurEngine/vendor/glfw/GLFW/src/win32_thread.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_thread.h"
    "FeurEngine/vendor/glfw/GLFW/src/win32_time.c"
    "FeurEngine/vendor/glfw/GLFW/src/win32_time.h"
    "FeurEngine/vendor/glfw/GLFW/src/win32_window.c"
    "FeurEngine/vendor/glfw/GLFW/src/window.c"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Debug-windows-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Debug-windows-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Debug-windows-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Debug>:_GLFW_WIN32>
  $<$<CONFIG:Debug>:_CRT_SECURE_NO_WARNINGS>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Release-windows-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Release-windows-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Release-windows-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Release>:_GLFW_WIN32>
  $<$<CONFIG:Release>:_CRT_SECURE_NO_WARNINGS>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)

target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Dist-windows-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Dist-windows-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/glfw/bin/Dist-windows-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Dist>:_GLFW_WIN32>
  $<$<CONFIG:Dist>:_CRT_SECURE_NO_WARNINGS>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
)
