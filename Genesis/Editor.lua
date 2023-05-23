
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

	includedirs {
		includeDirs["Genesis"],
		includeDirs["spdlog"],
		includeDirs["fmt"],
		includeDirs["glfw"],
		includeDirs["glm"],
		includeDirs["glad"],
		includeDirs["imgui"],
		includeDirs["stb"]
	}

	links {
		"ThirdParty.spdlog",
		--"ThirdParty.fmt",
		"ThirdParty.glfw",
		"Genesis.Core",
		"bx.lib",
		"bimg.lib",
		"bgfx.lib",
		"d3d12.lib"
	}
