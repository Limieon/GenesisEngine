outdir = "%{cfg.system}/%{cfg.longname}/%{prj.name}"
renderingAPI = "opengl"

include "dependencies.lua"

workspace "GenesisEngine"
	language "C++"
	cppdialect "C++20"
	systemversion "latest"

	if renderingAPI == "opengl" then
		defines { "GE_RENDERINGAPI_OPENGL" }
	end

	-- Global Defines
	defines { 
		"IMGUI_IMPL_OPENGL_LOADER_GLAD"
	}

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
		defines { "GE_ARCH_X64" }
		architecture("x86_64")
	filter "configurations:*x86"
		defines { "GE_ARCH_X86" }
		architecture("x86")
	filter ""

	filter "configurations:Debug*"
		defines { "GE_CFG_DEBUG", "_ITERATOR_DEBUG_LEVEL=2", "BX_CONFIG_DEBUG=1" }
		runtime "Debug"
	filter "configurations:Release*"
		defines { "GE_CFG_RELEASE", "GE_CFG_NDEBUG", "BX_CONFIG_DEBUG=0" }
		runtime "Release"
	filter "configurations:Dist*"
		defines { "GE_CFG_DIST", "GE_CFG_NDEBUG", "BX_CONFIG_DEBUG=0" }
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

	-- ThirdParty
	group "Dependencies"
	include "Dependencies/spdlog.lua"
	include "Dependencies/fmt.lua"

	-- Genesis
    group "Genesis"
	include "src/Genesis/Core.lua"
	include "src/Genesis/Server.lua"
	include "src/Genesis/Client.lua"
	include "src/Genesis/Editor.lua"

	-- Runtime
    group "Runtime"
    include "src/Runtime/Common.lua"
	include "src/Runtime/Client.lua"
	include "src/Runtime/Server.lua"
