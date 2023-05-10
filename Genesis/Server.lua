
group "Genesis"
project "Genesis.Server"
	kind "StaticLib"
	location "%{wks.location}/Genesis/src/GenesisServer/"

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
