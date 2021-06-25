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
IncludeDir["GLFW"] = "Adze/vendor/GLFW/include"
IncludeDir["Glad"] = "Adze/vendor/Glad/include"
IncludeDir["imgui"] = "Adze/vendor/imgui"
IncludeDir["glm"] = "Adze/vendor/glm"

include "Adze/vendor/GLFW"
include "Adze/vendor/Glad"
include "Adze/vendor/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
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
			"ADZE_ENABLE_ASSERTS",
			"GLFW_INCLUDE_NONE"
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
		"Adze/vendor/glm",
		"Adze/vendor/spdlog/include",
		"Hazel/vendor",
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
