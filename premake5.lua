workspace "Tayo"
	architecture "X64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tayo/vendor/GLFW/include"
IncludeDir["Glad"] = "Tayo/vendor/Glad/include"
IncludeDir["ImGui"] = "Tayo/vendor/imgui"


include "Tayo/vendor/GLFW"
include "Tayo/vendor/Glad"
include "Tayo/vendor/imgui"

project "Tayo"
	location "Tayo"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS",
			"TY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
		--("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		
		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TY_DIST"
		runtime "Release"
		optimize "On"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		staticruntime "off"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS"
		}

		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TY_DIST"
		runtime "Release"
		optimize "On"
