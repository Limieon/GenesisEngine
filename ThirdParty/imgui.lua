project "ThirdParty.imgui"
	kind "StaticLib"
	location "%{wks.location}/ThirdParty/imgui"

	files {
		"%{prj.location}/imgui_demo.cpp",
		"%{prj.location}/imgui_draw.cpp",
		"%{prj.location}/imgui_tables.cpp",
		"%{prj.location}/imgui_widgets.cpp",
		"%{prj.location}/imgui.cpp",

		"%{prj.location}/backends/imgui_impl_glfw.cpp",
		"%{prj.location}/backends/imgui_impl_opengl3.cpp"
	}

	includedirs {
		"%{prj.location}",
		includeDirs["glfw"]
	}

	filter "system:windows"
		files {
			"%{prj.location}/backends/imgui_impl_win32.cpp"
		}
	filter "system:macosx"
		files {
			"%{prj.location}/backends/imgui_impl_osx.cpp"
		}
