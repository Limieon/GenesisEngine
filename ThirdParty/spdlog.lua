
project "ThirdParty.spdlog"
	kind "StaticLib"
	location "%{wks.location}/ThirdParty/spdlog/"

	files {
		"%{prj.location}/src/async.cpp",
		"%{prj.location}/src/cfg.cpp",
		"%{prj.location}/src/color_sinks.cpp",
		"%{prj.location}/src/file_sinks.cpp",
		"%{prj.location}/src/spdlog.cpp",
		"%{prj.location}/src/stdout_sinks.cpp",
		"%{prj.location}/src/bundled_fmtlib_format.cpp"
	}

	defines {
		"SPDLOG_COMPILED_LIB"
	}

	includedirs {
		includeDirs["spdlog"]
	}
