project "assimp"
    location "build"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "assimp_compile.cpp"
    }

    includedirs
    {
        "$(ProjectDir)assimp/include"
    }
    
    filter "configurations:Release"
        links
        {
            "$(ProjectDir)assimp/lib/assimp"
        }
    
    filter "configurations:Debug"
        links
        {
            "$(ProjectDir)assimp/lib/lib/Debug/assimp-vc143-mtd",
            "$(ProjectDir)assimp/lib/contrib/zlib/Debug/zlibstaticd"
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
