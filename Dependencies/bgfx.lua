project "ThirdParty.bgfx"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/bgfx/"

    defines {
        "BGFX_CONFIG_MULTITHREADED=1",
        "BX_CONFIG_DEBUG=true",
        "BGFX_CONFIG_RENDERER_OPENGL=46",
        "PRIx64="
    }

    includedirs {
        includeDirs["bgfx"],
        includeDirs["bimg"],
        includeDirs["bx"],
        "%{prj.location}/3rdparty",
        "%{prj.location}/3rdparty/khronos"
    }

	filter "system:windows"
        files { "%{prj.location}/src/amalgamated.cpp" }

        includedirs {
            "%{wks.location}/Dependencies/bx/include/compat/msvc"
        }
		
		buildoptions { "/Zc:__cplusplus" }
    filter "system:linux"
        files { "%{prj.location}/src/amalgamated.cpp" }
    filter "system:macosx"
        files { "%{prj.location}/src/amalgamated.cpp" }
    filter ""
