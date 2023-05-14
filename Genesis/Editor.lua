
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
		includeDirs["fmt"]
	}

	links {
		"spdlog",
		"fmt"
	}
