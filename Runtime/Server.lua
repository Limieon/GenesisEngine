print("-- Runtime.Server")

group "Runtime"
project "Runtime.Server"
	kind "ConsoleApp"
	location "%{wks.location}/Runtime/src/RuntimeServer/"

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
		includeDirs["fmt"]
	}

	links {
		"ThirdParty.spdlog",
		"ThirdParty.fmt"
	}
