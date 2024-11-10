project "Nuklear"
    location "build"
    kind "StaticLib"
    language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Nuklear/src/**.h",
        "Nuklear/src/**.c"
    }

    defines
    {
        "NK_INCLUDE_FONT_BAKING"
    }
