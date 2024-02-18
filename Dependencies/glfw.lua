project "ThirdParty.glfw"
    kind "StaticLib"
    language "C"	
	location "%{wks.location}/Dependencies/glfw/"

    files {
		"%{prj.location}/include/GLFW/glfw3.h",
		"%{prj.location}/include/GLFW/glfw3native.h",
		"%{prj.location}/src/glfw_config.h",
		"%{prj.location}/src/context.c",
		"%{prj.location}/src/init.c",
		"%{prj.location}/src/input.c",
		"%{prj.location}/src/monitor.c",

		"%{prj.location}/src/null_init.c",
		"%{prj.location}/src/null_joystick.c",
		"%{prj.location}/src/null_monitor.c",
		"%{prj.location}/src/null_window.c",

		"%{prj.location}/src/platform.c",
		"%{prj.location}/src/vulkan.c",
		"%{prj.location}/src/window.c"
    }

	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files {
			"%{prj.location}/src/x11_init.c",
			"%{prj.location}/src/x11_monitor.c",
			"%{prj.location}/src/x11_window.c",
			"%{prj.location}/src/xkb_unicode.c",
			"%{prj.location}/src/posix_time.c",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_module.c",
			"%{prj.location}/src/glx_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/linux_joystick.c"
		}

		defines {
			"_GLFW_X11"
		}

	filter "system:macosx"
		pic "On"

		files {
			"%{prj.location}/src/cocoa_init.m",
			"%{prj.location}/src/cocoa_monitor.m",
			"%{prj.location}/src/cocoa_window.m",
			"%{prj.location}/src/cocoa_joystick.m",
			"%{prj.location}/src/cocoa_time.c",
			"%{prj.location}/src/nsgl_context.m",
			"%{prj.location}/src/posix_thread.c",
			"%{prj.location}/src/posix_module.c",
			"%{prj.location}/src/osmesa_context.c",
			"%{prj.location}/src/egl_context.c"
		}

		defines {
			"_GLFW_COCOA"
		}

	filter "system:windows"
		systemversion "latest"

		files {
			"%{prj.location}/src/win32_init.c",
			"%{prj.location}/src/win32_joystick.c",
			"%{prj.location}/src/win32_module.c",
			"%{prj.location}/src/win32_monitor.c",
			"%{prj.location}/src/win32_time.c",
			"%{prj.location}/src/win32_thread.c",
			"%{prj.location}/src/win32_window.c",
			"%{prj.location}/src/wgl_context.c",
			"%{prj.location}/src/egl_context.c",
			"%{prj.location}/src/osmesa_context.c"
		}

		links {
			"Dwmapi.lib"
		}

		defines  { 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
