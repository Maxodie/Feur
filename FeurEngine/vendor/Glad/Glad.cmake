message("==== Glad build (${CMAKE_BUILD_TYPE}) ====")

add_library("Glad" STATIC
      "FeurEngine/vendor/Glad/include/KHR/khrplatform.h"
      "FeurEngine/vendor/Glad/include/glad/glad.h"
    "FeurEngine/vendor/Glad/src/glad.c"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Glad" PROPERTIES
    OUTPUT_NAME "Glad"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Debug-windows-x86_64/Glad"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Debug-windows-x86_64/Glad"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Debug-windows-x86_64/Glad"
  )
endif()
target_include_directories("Glad" PRIVATE
  $<$<CONFIG:Debug>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/include>
)
target_compile_definitions("Glad" PRIVATE
)
target_link_directories("Glad" PRIVATE
)
target_link_libraries("Glad"
)
target_compile_options("Glad" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Glad" PROPERTIES
    OUTPUT_NAME "Glad"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Release-windows-x86_64/Glad"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Release-windows-x86_64/Glad"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Release-windows-x86_64/Glad"
  )
endif()
target_include_directories("Glad" PRIVATE
  $<$<CONFIG:Release>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/include>
)
target_compile_definitions("Glad" PRIVATE
)
target_link_directories("Glad" PRIVATE
)
target_link_libraries("Glad"
)
target_compile_options("Glad" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Glad" PROPERTIES
    OUTPUT_NAME "Glad"
    ARCHIVE_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Dist-windows-x86_64/Glad"
    LIBRARY_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Dist-windows-x86_64/Glad"
    RUNTIME_OUTPUT_DIRECTORY "E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/bin/Dist-windows-x86_64/Glad"
  )
endif()
target_include_directories("Glad" PRIVATE
  $<$<CONFIG:Dist>:E:/_prog/C/CProjects/FEUR/Feur/FeurEngine/vendor/Glad/include>
)
target_compile_definitions("Glad" PRIVATE
)
target_link_directories("Glad" PRIVATE
)
target_link_libraries("Glad"
)
target_compile_options("Glad" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
)
