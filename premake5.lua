workspace "Tayo"
	architecture "X64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tayo/vendor/GLFW/include"

include "Tayo/vendor/GLFW"

project "Tayo"
	location "Tayo"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .."/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader "typch.h"
	pchsource "Tayo/src/typch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS",
			"TY_BUILD_DLL",
			"TY_ENABLE_ASSERTS"
		}
		postbuildcommands
		{
		("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TY_DIST"
		optimize "On"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

	}

	includedirs
	{
		"Tayo/vendor/spdlog/include",
		"Tayo/src"
	}

	links
	{
		"Tayo"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS"
		}

		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "TY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TY_DIST"
		optimize "On"