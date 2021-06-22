project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("target/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/Glad/Glad.h",
		"include/Glad/Glad.h",
		"src/Glad.c"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"
