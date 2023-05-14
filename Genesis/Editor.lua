print("-- Genesis.Editor")

group "Genesis"
project "Genesis.Editor"
	kind "ConsoleApp"
	location "%{wks.location}/Genesis/src/GenesisEditor/"

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	defines {
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		includeDirs["Genesis"],
		includeDirs["spdlog"],
		includeDirs["fmt"],
		includeDirs["glfw"],
		includeDirs["vulkan"]
	}

	links {
		"Genesis.Core",
		"ThirdParty.spdlog",
		"ThirdParty.fmt",
		"ThirdParty.glfw",
		"vulkan-1.lib"
	}

	filter "system:windows"
		links { "user32.lib", "Winmm.lib" }
