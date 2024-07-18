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
IncludeDir["glm"] = "Tayo/vendor/glm"
IncludeDir["stb_image"] = "Tayo/vendor/stb_image"


include "Tayo/vendor/GLFW"
include "Tayo/vendor/Glad"
include "Tayo/vendor/imgui"

project "Tayo"
	location "Tayo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/%{prj.name}" )
	objdir ("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader "typch.h"
	pchsource "Tayo/src/typch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS",
			"TY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TY_DIST"
		runtime "Release"
		optimize "on"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Tayo/src",
		"Tayo/vendor",
		"Tayo/Tayo/Core",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Tayo"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TY_PLATFORM_WINDOWS"
		}

		
	filter "configurations:Debug"
		defines "TY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TY_DIST"
		runtime "Release"
		optimize "on"
