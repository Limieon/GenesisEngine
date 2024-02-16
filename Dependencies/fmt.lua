project "ThirdParty.fmt"
	kind "StaticLib"
	location "%{wks.location}/Dependencies/fmt/"

	files { "%{prj.location}/src/format.cc", "%{prj.location}/src/os.cc" }
	includedirs { includeDirs["fmt"] }
