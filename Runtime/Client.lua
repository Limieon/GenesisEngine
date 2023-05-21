
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
		includeDirs["glfw"],
		includeDirs["glm"],
		includeDirs["glad"]
	}

	links {
		"ThirdParty.spdlog",
		--"ThirdParty.fmt",
		"ThirdParty.glfw",
		"ThirdParty.glad",
		"Genesis.Client",
		"Genesis.Core"
	}
