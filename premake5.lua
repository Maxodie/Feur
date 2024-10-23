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
IncludeDir["nuklear"] = "Feur/vendor"
IncludeDir["Mathilda"] = "Feur/vendor/Mathilda/Mathilda/include"
IncludeDir["Vulkan"] = "Feur/vendor/VulkanSDK/1.3.290.0/Include"

IncludeLib = {}
IncludeLib["Vulkan"] = "Feur/vendor/VulkanSDK/1.3.290.0/Lib/vulkan-1.lib"

group "Dependencies"
	group "Window"
		include "Feur/vendor/GLFW"
		include "Feur/vendor/SDL2/SDL/SDL2.lua"
		include "Feur/vendor/SDL2/SDL/SDL2main.lua"

    group "Rendering"
		include "Feur/vendor/Glad/premake5.lua"
        include "Feur/vendor/VulkanSDK/Vulkan_premake.lua"

	group "GUI"
		include "Feur/vendor/Nuklear/nuklear.lua"

	group "Math"
		include "Feur/vendor/Mathilda/include_premake5.lua"

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
		"ILDA_HAVE_INLINE",
		"_CRT_SECURE_NO_WARNINGS",
        --"FE_RENDER_SELECTED_API_OPENGL",
		"FE_RENDER_SELECTED_API_VULKAN"
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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Vulkan}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.nuklear}",
		"%{IncludeDir.Mathilda}"
	}

	links
	{
		"SDL2",
		"SDL2main",
		"Glad",
		"GLFW",
		"Mathilda",
        "%{IncludeLib.Vulkan}"
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
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines "FE_DIST"
		runtime "Release"
		optimize "on"
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
		"%{IncludeDir.Mathilda}",
		--temp test includes
        "%{IncludeDir.Vulkan}",
		"%{IncludeDir.Glad}"
	}

	links
	{
		"Feur",
		"Mathilda",
        --temp test includes
        "Vulkan",
		"Glad"
	}

	defines
	{
		"ILDA_HAVE_INLINE",
		--"_FEUR_TEST_OPENGL_SANDBOX_"
		"_FEUR_TEST_VULKAN_SANDBOX_"
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
