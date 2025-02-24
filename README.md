# Feur
## Dependencies :
- [GLFW](https://github.com/glfw/glfw)
- [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear)
- Vulkan
- [Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
- [Mathilda](https://github.com/maxodie/Mathilda)
- [Assimp](https://github.com/assimp/assimp)
- Glad (not supported yet)
- SDL2 (not supported yet)

## Build :
Feur is currently using CMake. By default it also generate a compile\_commands.json.
Premake5 is depricated for now.

There are 3 build types : Debug; Release; Dist
### Exemples :
- build using mingw32 and Makefiles with the default configuration (Debug)
````
cmake -G "MinGW Makefiles" -S ./ -B ./build
mingw32-make -C ./build
````

- build using mingw32 and Makefiles with a defined configuration
````
cmake -G "MinGW Makefiles" -S ./ -B ./build -DCMAKE_BUILD_TYPE=<build_type>
mingw32-make -C ./build
````

### CMake flags list :
- CMAKE\_BUILD\_TYPE : values are `Debug`; `Release`; `Dist`;
- CMAKE\_EXPORT\_COMPILE\_COMMANDS : values are `ON`; `OFF`;
