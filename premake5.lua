outdir = "%{cfg.system}/%{cfg.longname}/%{prj.name}"

include "defines.lua"

workspace "GenesisEngine"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	configurations {
		"Debug-x64", "Release-x64", "Dist-x64",
		"Debug-x86", "Release-x86", "Dist-x86"
	}

	staticruntime "On"

	targetdir("%{wks.location}/bin/"..outdir)
	debugdir("%{wks.location}/bin/"..outdir)
	objdir("%{wks.location}/bin-int/"..outdir)
	includedirs { "%{wks.location}/include/" }

	filter "system:windows"
		libdirs("%{wks.location}/lib/win32/%{cfg.longname}")
	filter "system:linux"
		libdirs("%{wks.location}/lib/linux/%{cfg.longname}")
	filter "system:macosx"
		libdirs("%{wks.location}/lib/darwin/%{cfg.longname}")
	filter ""

	filter "configurations:*x64"
		defines { "GE_ARCHITECTURE_X64" }
		architecture("x86_64")
		libdirs {
			VULKAN_SDK_DIR.."/Lib"
		}
	filter "configurations:*x86"
		defines { "GE_ARCHITECTURE_X86" }
		architecture("x86")
		libdirs {
			VULKAN_SDK_DIR.."/Lib32"
		}
	filter ""

	filter "configurations:Debug*"
		optimize "Off"
		symbols "On"
		defines { "GE_CONFIG_DEBUG" }
		runtime "Debug"
	filter "configurations:Release*"
		optimize "Speed"
		symbols "Off"
		defines { "GE_CONFIG_RELEASE", "GE_CONFIG_NDEBUG" }
		runtime "Debug"
	filter "configurations:Dist*"
		optimize "Speed"
		symbols "Off"
		defines { "GE_CONFIG_DIST", "GE_CONFIG_NDEBUG" }
		runtime "Release"
	filter ""
	
	filter "system:windows"
		defines {"GE_PLATFORM_WINDOWS"}
	filter "system:linux"
		defines { "GE_PLATFORM_LINUX", "GE_PLATFORM_UNIX" }
	filter "system:macosx"
		defines { "GE_PLATFORM_MACOSX" }
	filter ""

	-- ThirdParty
	include "ThirdParty/spdlog.lua"
	include "ThirdParty/fmt.lua"
	include "ThirdParty/glfw.lua"
		
	-- Genesis
	include "Genesis/Core.lua"
	-- include "Genesis/Server.lua"
	include "Genesis/Client.lua"
	-- include "Genesis/Runtime.lua"
	include "Genesis/Editor.lua"

	-- Runtime
	include "Runtime/Client.lua"
	-- include "Runtime/Server.lua"
