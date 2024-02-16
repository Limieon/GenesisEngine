project "Genesis.Editor"
	kind "ConsoleApp"
	location "%{wks.location}/src/Genesis/Editor/"

	files {
		"%{prj.location}/**.c",
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp"
	}

	includedirs {
		includeDirs["Genesis"],
		includeDirs["spdlog"],
		includeDirs["fmt"]
	}

	links {
		"ThirdParty.spdlog",
		"ThirdParty.fmt",
		"Runtime.Common",
		"Genesis.Core",
		"Genesis.Server",
		"Genesis.Client"
	}
