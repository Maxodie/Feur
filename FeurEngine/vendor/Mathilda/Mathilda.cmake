message("==== Mathilda build (${CMAKE_BUILD_TYPE}) ====")

add_library("Mathilda" STATIC
    "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_core.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_matrix/ILDA_matrix.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_matrix/ILDA_matrix2x2_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_matrix/ILDA_matrix3x3_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_matrix/ILDA_matrix4x4_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_quaternion/ILDA_quaternion.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_trigo/ILDA_trigo.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_trigo/ILDA_trigo_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_utils/ILDA_utils.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_utils/ILDA_utils_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_utils/ILDA_utils_int.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_vector/ILDA_vector.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_vector/ILDA_vector_double.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_vector/ILDA_vector_float.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include/ILDA_vector/ILDA_vector_int.h"
    "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/ILDA_constants.h"
    "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/ILDA_main_test.c"
    "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/ILDA_type_off.h"
    "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/ILDA_type_on.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/matrix/ILDA_matrix_link.c"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/matrix/ILDA_matrix_size_off.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/matrix/ILDA_matrix_size_on.h"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/quaternion/ILDA_quaternion_float.c"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/trigo/ILDA_trigo_float.c"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/utils/ILDA_utils_link.c"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/vector/ILDA_vector_link.c"
      "FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src/vector/ILDA_vector_special_float.c"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Mathilda" PROPERTIES
    OUTPUT_NAME "Mathilda"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Debug-windows-x86_64/Mathilda"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Debug-windows-x86_64/Mathilda"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Debug-windows-x86_64/Mathilda"
  )
endif()
target_include_directories("Mathilda" PRIVATE
  $<$<CONFIG:Debug>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include>
  $<$<CONFIG:Debug>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src>
)
target_compile_definitions("Mathilda" PRIVATE
  $<$<CONFIG:Debug>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Debug>:ILDA_FORCE_LEFT_HANDED>
  $<$<CONFIG:Debug>:ILDA_DEBUG>
  $<$<CONFIG:Debug>:ILDA_ENABLE_ASSERTS>
)
target_link_directories("Mathilda" PRIVATE
)
target_link_libraries("Mathilda"
)
target_compile_options("Mathilda" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Mathilda" PROPERTIES
    OUTPUT_NAME "Mathilda"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Release-windows-x86_64/Mathilda"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Release-windows-x86_64/Mathilda"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Release-windows-x86_64/Mathilda"
  )
endif()
target_include_directories("Mathilda" PRIVATE
  $<$<CONFIG:Release>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include>
  $<$<CONFIG:Release>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src>
)
target_compile_definitions("Mathilda" PRIVATE
  $<$<CONFIG:Release>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Release>:ILDA_FORCE_LEFT_HANDED>
  $<$<CONFIG:Release>:ILDA_RELEASE>
  $<$<CONFIG:Release>:ILDA_ENABLE_ASSERTS>
)
target_link_directories("Mathilda" PRIVATE
)
target_link_libraries("Mathilda"
)
target_compile_options("Mathilda" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Mathilda" PROPERTIES
    OUTPUT_NAME "Mathilda"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Dist-windows-x86_64/Mathilda"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Dist-windows-x86_64/Mathilda"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/bin/Dist-windows-x86_64/Mathilda"
  )
endif()
target_include_directories("Mathilda" PRIVATE
  $<$<CONFIG:Dist>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/include>
  $<$<CONFIG:Dist>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Mathilda/Mathilda/Mathilda/src>
)
target_compile_definitions("Mathilda" PRIVATE
  $<$<CONFIG:Dist>:ILDA_HAVE_INLINE>
  $<$<CONFIG:Dist>:ILDA_FORCE_LEFT_HANDED>
  $<$<CONFIG:Dist>:ILDA_DIST>
)
target_link_directories("Mathilda" PRIVATE
)
target_link_libraries("Mathilda"
)
target_compile_options("Mathilda" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-std=c17>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
