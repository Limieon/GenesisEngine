project "ThirdParty.lodepng"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/lodepng/"

	files {
		"%{prj.location}/lodepng.cpp"
	}

	includedirs {
		includeDirs["lodepng"]
	}
