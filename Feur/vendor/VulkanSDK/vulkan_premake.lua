project ("Vulkan")
    location "build"
    kind "StaticLib"
    language "C"

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

    --libdirs
    --{
        --"$(ProjectDir)1.3.290.0/Lib"
    --}

    links
    {
        "$(ProjectDir)../1.3.290.0/Lib/vulkan-1.lib",
        "$(ProjectDir)../1.3.290.0/Lib/shaderc_shared.lib",
    }

    includedirs
    {
        "$(ProjectDir)../1.3.290.0/Include"
    }

    defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        defines { "WIN32", "_DEBUG", "DEBUG", "_WINDOWS" }
        symbols "on"
        optimize "On"
        systemversion "latest"
        staticruntime "On"
        runtime "Debug"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        symbols "on"
        systemversion "latest"
        staticruntime "On"
     
    filter "configurations:Release"
        defines { "WIN32", "NDEBUG", "PROFILE", "_WINDOWS" }





project ("VulkanMemoryAllocator")
    location "build"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    links
    {
        "Vulkan"
    }

    files
    {
        "VulkanMemoryAllocator/include/**.h",
        "VulkanMemoryAllocatorCompile.cpp"
    }

    includedirs
    {
        "$(ProjectDir)../1.3.290.0/Include"
    }

    filter "system:linux"
        systemversion "latest"
        staticruntime "on"
    
    filter "system:windows"
        linkoptions { "/NODEFAULTLIB:library" }
        systemversion "latest"
        staticruntime "on"

        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"
