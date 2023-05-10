outdir = "%{cfg.system}/%{cfg.longname}/%{prj.name}"

include "defines.lua"

workspace "GenesisEngine"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	targetdir("%{wks.location}/bin/"..outdir)
	debugdir("%{wks.location}/bin/"..outdir)
	objdir("%{wks.location}/bin-int/"..outdir)
	libdirs("%{wks.location}/lib/%{cfg.system}/%{cfg.longname}")
	includedirs { "%{wks.location}/include/" }

	configurations {
		"Debug-x64", "Release-x64", "Dist-x64",
		"Debug-x86", "Release-x86", "Dist-x86"
	}

	filter "configurations:*x64"
		defines { "GE_ARCHITECTURE_X64" }
		architecture("x86_64")
	filter "configurations:*x86"
		defines { "GE_ARCHITECTURE_X86" }
		architecture("x86")
	filter ""

	filter "configurations:Debug*"
		defines { "GE_CONFIG_DEBUG" }
	filter "configurations:Release*"
		defines { "GE_CONFIG_RELEASE", "GE_CONFIG_NDEBUG" }
	filter "configurations:Dist*"
		defines { "GE_CONFIG_DIST", "GE_CONFIG_NDEBUG" }
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
		
	-- Genesis
	include "Genesis/Core.lua"
	-- include "Genesis/Server.lua"
	include "Genesis/Client.lua"
	-- include "Genesis/Runtime.lua"
	-- include "Genesis/Editor.lua"

	-- Runtime
	include "Runtime/Client.lua"
	-- include "Runtime/Server.lua"
