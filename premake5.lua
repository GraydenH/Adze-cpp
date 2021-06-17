workspace "Engine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildscfg}-%{cfg.system}-%{cfg.architecture}"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("target/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ENGINE_PLATFORM_WINDOWS",
			"ENGINE_BUILD_DLL",
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../target/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGINE_DIST"
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
		"Engine/vendor/spdlog/include",
		"Engine/src"
	}

	links {
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGINE_DIST"
		optimize "On"