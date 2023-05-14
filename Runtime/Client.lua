print("-- Runtime.Client")

group "Runtime"
project "Runtime.Client"
	kind "ConsoleApp"
	location "%{wks.location}/Runtime/src/RuntimeClient/"

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Genesis"],
		includeDirs["Runtime"],
		includeDirs["spdlog"],
		includeDirs["fmt"],
		includeDirs["glfw"]
	}

	links {
		"ThirdParty.spdlog",
		"ThirdParty.fmt",
		"Genesis.Client",
		"Genesis.Core",
		"bx.lib",
		"bimg.lib",
		"bgfx.lib",
		"ThirdParty.glfw"
	}
