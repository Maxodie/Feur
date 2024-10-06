project ("Vulkan")
    kind "StaticLib"
    language "C"
    uuid "4ABD8B07-B672-04FD-3F67-FED3AB1BFB00"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    warnings "Extra"
    floatingpoint "Fast"

    -- Specify WindowsTargetPlatformVersion here for VS2015

    files {
        "1.3.290.0/Source/**.h",
        "1.3.290.0/Source/**.c",
        "1.3.290.0/Include/**.h"

    }

    links { "$(ProjectDir)1.3.290.0/Lib/vulkan-1.lib" }
    includedirs { "$(ProjectDir)1.3.290.0/Include" }

    defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        defines { "WIN32", "_DEBUG", "DEBUG", "_WINDOWS" }
        symbols "on"

    filter "configurations:Release"
        defines { "WIN32", "NDEBUG", "PROFILE", "_WINDOWS" }
        symbols "on"
        optimize "On"
