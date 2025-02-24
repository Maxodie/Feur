cmake_minimum_required(VERSION 3.30)
project(FeurEngine VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON" CACHE STRING "export compile commands.")
message("==== Feur export compile commands set to ${CMAKE_EXPORT_COMPILE_COMMANDS} ====")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${CMAKE_EXPORT_COMPILE_COMMANDS}")

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    message("==== Feur create .clang file to store 'CompilationDatabase: build/' ====")
    file(WRITE ".clang"
        "CompileFlags:
            CompilationDatabase: build/"
    )
endif()

if (NOT DEFINED ARCHITECTURE)
    if (CMAKE_SIZEOF_VOID_P GREATER 4)
        set(ARCHITECTURE x64_x86)
    else()
        set(ARCHITECTURE x32)
    endif()
endif()

set(FEUR_BUILD_TYPES "Debug" "Release" "Dist")
get_property(multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(multi_config)
    set(CMAKE_CONFIGURATION_TYPES "${FEUR_BUILD_TYPES}" CACHE STRING "list of supported configuration types" FORCE)
else()
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build Type of the project.")
    message("==== Feur last/default build type selected (${CMAKE_BUILD_TYPE}) ====")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${FEUR_BUILD_TYPES}")
endif()


if(NOT CMAKE_BUILD_TYPE IN_LIST FEUR_BUILD_TYPES)
    message(FATAL_ERROR
      "Invalid build type '${CMAKE_BUILD_TYPE}'.
      CMAKE_BUILD_TYPE must be any one of the possible values:
      ${FEUR_BUILD_TYPES}"
    )
endif()

message("==== Feur build (${CMAKE_BUILD_TYPE}) ====")

set(FE_BIN_OUTPUT_DIR "/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${ARCHITECTURE}")
set(FE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}${FE_BIN_OUTPUT_DIR}")


set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_C_FLAGS_DIST "")
set(CMAKE_CXX_FLAGS_DIST "")

project(Feur)
include(FeurEngine/FeurEngine.cmake)
include(Sandbox/Sandbox.cmake)
include(FeurEngine/vendor/nuklear/Nuklear.cmake)
include(FeurEngine/vendor/Mathilda/Mathilda.cmake)
include(FeurEngine/vendor/assimp/assimp.cmake)
include(FeurEngine/vendor/Glad/Glad.cmake)
include(FeurEngine/vendor/VulkanSDK/Vulkan.cmake)
include(FeurEngine/vendor/VulkanSDK/VulkanMemoryAllocator.cmake)
include(FeurEngine/vendor/glfw/GLFW.cmake)
