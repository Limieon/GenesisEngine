project "ThirdParty.glad"
	language "C"
	kind "StaticLib"
	location "./glad/"

	includedirs {
		"%{prj.location}/include/"	
	}
	files {
		"%{prj.location}/src/glad.c"
	}
