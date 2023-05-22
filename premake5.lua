outdir = "%{cfg.system}/%{cfg.longname}/%{prj.name}"
renderingAPI = "opengl"

include "defines.lua"

workspace "GenesisEngine"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	if renderingAPI == "opengl" then
		defines {"GE_RENDERINGAPI_OPENGL"}
	end

	-- Global Defines
	--defines { "SPDLOG_FMT_EXTERNAL" }

	staticruntime "On"

	targetdir("%{wks.location}/bin/"..outdir)
	debugdir("%{wks.location}/bin/"..outdir)
	objdir("%{wks.location}/bin-int/"..outdir)
	includedirs { "%{wks.location}/include/" }

	configurations {
		"Debug-x64", "Release-x64", "Dist-x64",
		"Debug-x86", "Release-x86", "Dist-x86"
	}

	filter "system:windows"
		libdirs("%{wks.location}/lib/win32/%{cfg.longname}")
	filter ""

	filter "configurations:*x64"
		defines { "GE_ARCHITECTURE_X64" }
		architecture("x86_64")
	filter "configurations:*x86"
		defines { "GE_ARCHITECTURE_X86" }
		architecture("x86")
	filter ""

	filter "configurations:Debug*"
		defines { "GE_CONFIG_DEBUG", "_ITERATOR_DEBUG_LEVEL=2", "BX_CONFIG_DEBUG=1" }
		runtime "Debug"
	filter "configurations:Release*"
		defines { "GE_CONFIG_RELEASE", "GE_CONFIG_NDEBUG", "BX_CONFIG_DEBUG=0" }
		runtime "Release"
	filter "configurations:Dist*"
		defines { "GE_CONFIG_DIST", "GE_CONFIG_NDEBUG", "BX_CONFIG_DEBUG=0" }
		runtime "Release"
	filter ""
	
	filter "system:windows"
		defines {"GE_PLATFORM_WINDOWS"}

		buildoptions { "/Zc:__cplusplus" }
	filter "system:linux"
		defines { "GE_PLATFORM_LINUX", "GE_PLATFORM_UNIX" }
	filter "system:macosx"
		defines { "GE_PLATFORM_MACOSX" }
	filter ""

	group "ThirdParty"
	-- ThirdParty
	include "ThirdParty/spdlog.lua"
	-- include "ThirdParty/fmt.lua"
	include "ThirdParty/glfw.lua"
	include "ThirdParty/glad.lua"
	group ""
		
	-- Genesis
	include "Genesis/Core.lua"
	-- include "Genesis/Server.lua"
	include "Genesis/Client.lua"
	-- include "Genesis/Runtime.lua"
	include "Genesis/Editor.lua"

	-- Runtime
	include "Runtime/Client.lua"
	-- include "Runtime/Server.lua"
