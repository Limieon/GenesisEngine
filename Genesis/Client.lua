
group "Genesis"
project "Genesis.Client"
	kind "StaticLib"
	location "%{wks.location}/Genesis/src/GenesisClient/"

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
		includeDirs["glad"]
	}
