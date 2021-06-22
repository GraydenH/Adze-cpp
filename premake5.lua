workspace "Adze"
	architecture "x64"

	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildscfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ADZE/vendor/GLFW/include"

include "Adze/vendor/GLFW"

project "Adze"
	location "Adze"
	kind "SharedLib"
	language "C++"

	targetdir ("target/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "adzepch.h"
	pchsource "Adze/src/adzepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"ADZE_PLATFORM_WINDOWS",
			"ADZE_BUILD_DLL",
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../target/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines {
			"ADZE_DEBUG",
			"ADZE_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines "ADZE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ADZE_DIST"
		optimize "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("target/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"Adze/vendor/spdlog/include",
		"Adze/src"
	}

	links {
		"Adze"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ADZE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ADZE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ADZE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ADZE_DIST"
		optimize "On"
