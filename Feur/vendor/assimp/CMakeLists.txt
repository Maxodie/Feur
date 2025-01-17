cmake_minimum_required(VERSION 3.15)

project(TARGET_MODEL_LOADER)

# Disable tests build
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable Tests build" FORCE)
# Disable treating warnings as errors
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat warnings as errors" FORCE)
# Disable Assimp's export functionality
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Disable Assimp export functionality" FORCE)
# Enable static library instead of shared
set(ASSIMP_BUILD_STATIC_LIB ON CACHE BOOL "Build Assimp as a static library" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)
set(ASSIMP_BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)
# Set additional options as needed
set(ASSIMP_INSTALL OFF CACHE BOOL "Don't install Assimp" FORCE)

set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Don't install Assimp" FORCE)

set(USE_STATIC_CRT ON CACHE BOOL "use static msvc" FORCE)
# Use static runtime for MinGW (clang) or MSVC
if(MSVC)
    # For MSVC, use the /MTd flag (static debug)
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
    set(CMAKE_C_FLAGS_DEBUG "/MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_C_FLAGS_RELEASE "/MT")
    set(STATIC_LIBRARY_FLAGS "/NODEFAULTLIB:msvcrt.lib")
else()
    # For MinGW (clang), use the appropriate static linking flags
    set(STATIC_LIBRARY_FLAGS "-nodefaultlibs")
endif()


set(ASSIMP_INCLUDE_DIRS "{CMAKE_SOURCE_DIR}/assimp/include" "{CMAKE_SOURCE_DIR}/build/assimp/include")
include_directories(${ASSIMP_INCLUDE_DIRS})
add_subdirectory(assimp)
#find_package(assimp REQUIRED)
add_library(TARGET_MODEL_LOADER INTERFACE)


target_link_libraries(TARGET_MODEL_LOADER INTERFACE assimp::assimp)
