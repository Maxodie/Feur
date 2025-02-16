message("==== Nuklear build (${CMAKE_BUILD_TYPE}) ====")

add_library("Nuklear" STATIC
      "FeurEngine/vendor/nuklear/NuklearImplementationCompile.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear.h"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_9slice.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_buffer.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_button.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_chart.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_color.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_color_picker.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_combo.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_context.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_contextual.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_draw.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_edit.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_font.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_group.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_image.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_input.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_internal.h"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_knob.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_layout.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_list_view.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_math.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_menu.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_page_element.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_panel.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_pool.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_popup.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_progress.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_property.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_scrollbar.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_selectable.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_slider.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_string.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_style.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_table.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_text.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_text_editor.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_toggle.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_tooltip.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_tree.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_utf8.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_util.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_vertex.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_widget.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/nuklear_window.c"
      "FeurEngine/vendor/nuklear/Nuklear/src/stb_rect_pack.h"
      "FeurEngine/vendor/nuklear/Nuklear/src/stb_truetype.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Nuklear" PROPERTIES
    OUTPUT_NAME "Nuklear"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Debug-windows-x86_64/Nuklear"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Debug-windows-x86_64/Nuklear"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Debug-windows-x86_64/Nuklear"
  )
endif()
target_include_directories("Nuklear" PRIVATE
  $<$<CONFIG:Debug>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/Nuklear>
)

target_compile_definitions("Nuklear" PRIVATE
    NK_IMPLEMENTATION
    NK_INCLUDE_FONT_BAKING
    NK_INCLUDE_FIXED_TYPES
    NK_INCLUDE_STANDARD_IO
    NK_INCLUDE_STANDARD_VARARGS
    NK_INCLUDE_DEFAULT_ALLOCATOR
    NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    NK_INCLUDE_FONT_BAKING
    NK_INCLUDE_DEFAULT_FONT
    NK_KEYSTATE_BASED_INPUT
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Nuklear" PROPERTIES COMPILE_FLAGS "-Wno-implicit-function-declaration ")
endif()

target_compile_options("Nuklear" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Nuklear" PROPERTIES
    OUTPUT_NAME "Nuklear"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Release-windows-x86_64/Nuklear"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Release-windows-x86_64/Nuklear"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Release-windows-x86_64/Nuklear"
  )
endif()

target_include_directories("Nuklear" PRIVATE
  $<$<CONFIG:Release>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/Nuklear>
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Nuklear" PROPERTIES COMPILE_FLAGS "-Wno-implicit-function-declaration ")
endif()

target_compile_options("Nuklear" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Nuklear" PROPERTIES
    OUTPUT_NAME "Nuklear"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Dist-windows-x86_64/Nuklear"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Dist-windows-x86_64/Nuklear"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/bin/Dist-windows-x86_64/Nuklear"
  )
endif()

target_include_directories("Nuklear" PRIVATE
  $<$<CONFIG:Dist>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/nuklear/Nuklear>
)

if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Nuklear" PROPERTIES COMPILE_FLAGS "-Wno-implicit-function-declaration ")
endif()

target_compile_options("Nuklear" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
)
