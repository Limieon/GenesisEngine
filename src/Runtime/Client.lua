project "Runtime.Client"
	kind "ConsoleApp"
	location "%{wks.location}/src/Runtime/Client/"

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
		includeDirs["bgfx"],
		includeDirs["bx"],
		includeDirs["bimg"],
		includeDirs["imgui"],
		includeDirs["glfw"],
		includeDirs["glm"]
	}

	filter "system:windows"
        includedirs {
            "%{wks.location}/Dependencies/bx/include/compat/msvc"
        }

	links {
		"ThirdParty.spdlog",
		"ThirdParty.fmt",
		"ThirdParty.bgfx",
		"ThirdParty.bimg",
		"ThirdParty.bx",
		"ThirdParty.lodepng",
		"ThirdParty.glfw",
		"Runtime.Common",
		"Genesis.Core",
		"Genesis.Server",
		"Genesis.Client",

		"psapi",
		"OpenGL32.lib"
	}
