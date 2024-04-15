workspace "Feur"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SDL2"] = "Feur/vendor/SDL2/include"

IncludeLib = {}
group "Dependencies"
	include "Feur/vendor/SDL2/SDL2.lua"
	include "Feur/vendor/SDL2/SDL2main.lua"

project "Feur"
	location "Feur"
	kind "StaticLib"
	language "C"
	cdialect "C99"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fepch.h"
	pchsource "Feur/src/fepch.c"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	libdirs
	{
		"%{IncludeLib.SDL2}"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.SDL2}"
	}

	links
	{
		"SDL2",
		"SDL2main"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NT_PLATFORM_WINDOWS",
			"NT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NT_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "NT_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C"
	cdialect "C99"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
	}

	libdirs
	{
		"%{IncludeLib.SDL2}"
	}

	includedirs
	{
		"Feur/vendor/spdlog/include",
		"Feur/src",
	}

	links
	{
		"Feur"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NT_DIST"
		runtime "Release"
		optimize "on"