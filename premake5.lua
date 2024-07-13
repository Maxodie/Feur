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
IncludeDir["SDL2"] = "Feur/vendor/SDL2/SDL/include"
IncludeDir["Glad"] = "Feur/vendor/Glad/include"
IncludeDir["GLFW"] = "Feur/vendor/GLFW/include"
IncludeDir["nuklear"] = "Feur/vendor/Nuklear/"

IncludeLib = {}
group "Dependencies"
	group "Window"
		include "Feur/vendor/GLFW"
		include "Feur/vendor/SDL2/SDL/SDL2.lua"
		include "Feur/vendor/SDL2/SDL/SDL2main.lua"
	
	group "Rendering"
		include "Feur/vendor/Glad"

	group "GUI"
		include "Feur/vendor/Nuklear/nuklear/nuklear.lua"

group "Feur"

project "Feur"
	location "Feur"
	kind "StaticLib"
	language "C"
	cdialect "C17"
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
		"_CRT_SECURE_NO_WARNINGS",
		"NK_IMPLEMENTATION"
	}

	libdirs
	{
		"%{IncludeLib.SDL2}"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.nuklear}"
	}

	links
	{
		"SDL2",
		"SDL2main",
		"Glad",
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines
		{
			"FE_DEBUG",
			"FE_ENABLE_ASSERTS"
		}
		defines "FE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"FE_RELEASE",
			"FE_ENABLE_ASSERTS"
		}
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "FE_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C"
	cdialect "C17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c"
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
			"FE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines
		{
			"FE_DEBUG",
			"FE_ENABLE_ASSERTS"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"FE_RELEASE",
			"FE_ENABLE_ASSERTS"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FE_DIST"
		runtime "Release"
		optimize "on"