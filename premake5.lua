workspace "OneTrick"
    configurations {"Debug", "Release"}
    
project "OneTrick"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs{"src/Core", "src/Game", "src/Window", "src/Rendering"}
    files {"src/**.cpp", "src/**.h"}
    libdirs{"lib/SDL3/lib/x64"}
        links{"SDL3"}
        includedirs{"lib/SDL3/include"}
        architecture "x64"
    links { "d3d11", "dxgi", "d3dcompiler"}
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On" 
    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

project "Shaders"
    kind "None"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs{"Asset/**"}
    files {"src/**.hlsl"}
    links { "d3d11", "dxgi", "d3dcompiler" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On" 
    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

