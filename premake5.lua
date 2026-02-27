workspace "OneTrick"
    configurations {"Debug", "Release"}
    
project "OneTrick"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    targetdir "bin/%{cfg.buildcfg}"
    files {"src/**.cpp", "src/**.h"}
    links { "d3d11", "dxgi", "d3dcompiler" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On" 
    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
