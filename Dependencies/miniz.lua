project "ThirdParty.miniz"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/miniz/"

	files {
		"%{prj.location}/**.c"
	}
