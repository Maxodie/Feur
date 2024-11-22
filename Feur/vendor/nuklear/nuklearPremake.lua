project "Nuklear"
    location "build"
    kind "StaticLib"
    language "C"

    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Nuklear/src/**.h",
        "Nuklear/src/**.c",
        "NuklearImplementationCompile.c"
    }

    includedirs
    {
        "Nuklear"
    }

    defines
    {
        "NK_INCLUDE_FONT_BAKING"
    }
