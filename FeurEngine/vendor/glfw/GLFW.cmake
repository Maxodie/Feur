message("==== GLFW3 build (${CMAKE_BUILD_TYPE}) ====")

add_library("GLFW" STATIC
        FeurEngine/vendor/glfw/GLFW/include/GLFW/glfw3.h
        FeurEngine/vendor/glfw/GLFW/include/GLFW/glfw3native.h
    FeurEngine/vendor/glfw/GLFW/src/context.c
    FeurEngine/vendor/glfw/GLFW/src/egl_context.c
    FeurEngine/vendor/glfw/GLFW/src/init.c
    FeurEngine/vendor/glfw/GLFW/src/input.c
    FeurEngine/vendor/glfw/GLFW/src/internal.h
    FeurEngine/vendor/glfw/GLFW/src/mappings.h
    FeurEngine/vendor/glfw/GLFW/src/monitor.c
    FeurEngine/vendor/glfw/GLFW/src/null_init.c
    FeurEngine/vendor/glfw/GLFW/src/null_joystick.c
    FeurEngine/vendor/glfw/GLFW/src/null_joystick.h
    FeurEngine/vendor/glfw/GLFW/src/null_monitor.c
    FeurEngine/vendor/glfw/GLFW/src/null_platform.h
    FeurEngine/vendor/glfw/GLFW/src/null_window.c
    FeurEngine/vendor/glfw/GLFW/src/osmesa_context.c
    FeurEngine/vendor/glfw/GLFW/src/platform.c
    FeurEngine/vendor/glfw/GLFW/src/platform.h
    FeurEngine/vendor/glfw/GLFW/src/vulkan.c
    FeurEngine/vendor/glfw/GLFW/src/wgl_context.c
    FeurEngine/vendor/glfw/GLFW/src/win32_init.c
    FeurEngine/vendor/glfw/GLFW/src/win32_joystick.c
    FeurEngine/vendor/glfw/GLFW/src/win32_module.c
    FeurEngine/vendor/glfw/GLFW/src/win32_monitor.c
    FeurEngine/vendor/glfw/GLFW/src/win32_platform.h
    FeurEngine/vendor/glfw/GLFW/src/win32_thread.c
    FeurEngine/vendor/glfw/GLFW/src/win32_thread.h
    FeurEngine/vendor/glfw/GLFW/src/win32_time.c
    FeurEngine/vendor/glfw/GLFW/src/win32_time.h
    FeurEngine/vendor/glfw/GLFW/src/win32_window.c
    FeurEngine/vendor/glfw/GLFW/src/window.c
)

set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/GLFW"
)

target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Debug>:_GLFW_WIN32>
  $<$<CONFIG:Debug>:_CRT_SECURE_NO_WARNINGS>


  $<$<CONFIG:Release>:_GLFW_WIN32>
  $<$<CONFIG:Release>:_CRT_SECURE_NO_WARNINGS>


  $<$<CONFIG:Dist>:_GLFW_WIN32>
  $<$<CONFIG:Dist>:_CRT_SECURE_NO_WARNINGS>
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>


  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>


  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
)
