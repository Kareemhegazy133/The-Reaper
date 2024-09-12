workspace "TheReaper"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Game"
   
   flags
	{
		"MultiProcessorCompile"
	}

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      defines { "_CRT_SECURE_NO_WARNINGS" }
	  disablewarnings { "4996" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "Engine/Vendor/spdlog/include"
IncludeDir["sfml"] = "Engine/Vendor/sfml/include"
IncludeDir["entt"] = "Engine/Vendor/entt/include"
IncludeDir["box2d"] = "Engine/Vendor/box2d/include"
IncludeDir["yaml_cpp"] = "Engine/Vendor/yaml-cpp/include"
IncludeDir["glm"] = "Engine/Vendor/glm"

group "Dependencies"
	include "Engine/Vendor/box2d"
	include "Engine/Vendor/yaml-cpp"
	
group ""

project "Engine"
	kind "StaticLib"
	location "Engine"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	pchheader "%{prj.name}pch.h"
	pchsource "%{prj.name}/Source/%{prj.name}pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Vendor/glm/glm/**.hpp",
		"%{prj.name}/Vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.sfml}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.box2d}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"%{prj.name}/Vendor/sfml/lib"
	}
	
	links
	{
		"box2d",
		"yaml-cpp"
	}
	
	defines
	{
		"YAML_CPP_STATIC_DEFINE"
	}

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
	systemversion "latest"

	filter "configurations:Debug"
		defines { "ENGINE_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "ENGINE_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines { "ENGINE_DIST" }
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",

		-- Include Engine
		"Engine/Source",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.sfml}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.box2d}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"Engine/Vendor/sfml/lib"
	}

	links
	{
		"Engine"
	}

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "WINDOWS" }

	filter "configurations:Debug"
		defines { "GAME_DEBUG" }
		runtime "Debug"
		symbols "on"
		
		links
		{
			"sfml-audio-d.lib",
			"sfml-graphics-d.lib",
			"sfml-network-d.lib",
			"sfml-system-d.lib",
			"sfml-window-d.lib"
		}
		
		postbuildcommands
		{
			"{COPY} %{prj.location}/../Engine/Vendor/sfml/dlls/Debug/*.dll %{cfg.targetdir}"
        }

	filter "configurations:Release"
		defines { "GAME_RELEASE" }
		runtime "Release"
		optimize "on"

		links
		{
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
		
		postbuildcommands
		{
			"{COPY} %{prj.location}/../Engine/Vendor/sfml/dlls/Release/*.dll %{cfg.targetdir}"
        }

	filter "configurations:Dist"
		defines { "GAME_DIST" }
		runtime "Release"
		optimize "on"

		links
		{
			"sfml-audio.lib",
			"sfml-graphics.lib",
			"sfml-network.lib",
			"sfml-system.lib",
			"sfml-window.lib"
		}
		
		postbuildcommands
		{
			"{COPY} %{prj.location}/../Engine/Vendor/sfml/dlls/Release/*.dll %{cfg.targetdir}"
        }
