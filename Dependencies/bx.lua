project "ThirdParty.bx"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/bx/"

	files {
        "%{prj.location}/src/amalgamated.cpp"
    }

    defines {
        "PRIx64=",
        "PRIxPTR="
    }

    filter "system:windows"
        includedirs {
            "%{prj.location}/include/compat/msvc"
        }

    includedirs {
        "%{prj.location}",
        includeDirs["bx"],
        "%{prj.location}/3rdparty"
    }
