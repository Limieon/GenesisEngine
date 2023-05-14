print("-- Genesis.Runtime")

group "Genesis"
project "Genesis.Runtime"
	kind "StaticLib"
	location "%{wks.location}/Genesis/src/GenesisRuntime/"

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
