project "ThirdParty.bimg"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/bimg/"

	files {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/3rdparty/iqa/source/**.c",
        "%{prj.location}/3rdparty/tinyexr/deps/miniz/miniz.c",
        "%{prj.location}/3rdparty/astc-encoder/source/**.cpp"
    }

    filter "system:windows"
        includedirs {
            "%{wks.location}/Dependencies/bx/include/compat/msvc/"
        }

    defines {
    }

    includedirs {
        includeDirs["bgfx"],
        includeDirs["bimg"],
        includeDirs["bx"],
        includeDirs["lodepng"],

        "%{prj.location}/3rdparty",
        "%{prj.location}/3rdparty/tinyexr/deps/miniz",
        "%{prj.location}/3rdparty/astc-encoder/include/",
        "%{prj.location}/3rdparty/iqa/include"
    }
