workspace "lwlog"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "lwlog"
	location "lwlog"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/lwlog/**.h",
		"%{prj.name}/lwlog/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LWLOG_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "LWLOG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LWLOG_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"lwlog"
	}

	links
	{
		"lwlog"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "LWLOG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LWLOG_RELEASE"
		runtime "Release"
		optimize "on"