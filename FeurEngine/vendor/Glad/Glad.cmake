message("==== Glad build (${CMAKE_BUILD_TYPE}) ====")

add_library(Glad STATIC
      FeurEngine/vendor/Glad/include/KHR/khrplatform.h
      FeurEngine/vendor/Glad/include/glad/glad.h
    FeurEngine/vendor/Glad/src/glad.c
)

set_target_properties(Glad PROPERTIES
    OUTPUT_NAME Glad
    ARCHIVE_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Glad"
    LIBRARY_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Glad"
    RUNTIME_OUTPUT_DIRECTORY "${FE_OUTPUT_DIR}/Glad"
)

target_include_directories(Glad PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/FeurEngine/vendor/Glad/include"
)

target_compile_options(Glad PRIVATE
    -m64

    $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>

    $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>


    $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O2>
)
