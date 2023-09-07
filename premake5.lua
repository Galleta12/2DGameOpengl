-- premake5.lua


workspace "Game2DOpenGL" -- Name of sln file
    location "." -- Folder where to put it
    configurations { "Debug", "Release" }
    platforms { "Win32", "x64" }

    --Set architecture
    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"
    
    filter { "platforms:x64" }
        system "Windows"
        architecture "x64"

    filter { }


project "Game2DOpenGL" -- Name of project
    kind "ConsoleApp" -- Uses the console
    language "C++"
    location "." -- location of vcxproj file
    
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}" -- .exe files is in bin/(debug or release)/(x86 or x64)/
    --location of source files to include. Here we include All files ending with .h and .cpp
    --in the folder Minimal Example even files in subfolders.
    files { "./include/headers/**.h","./src/**.cpp" }
   
  
    externalincludedirs {  
        "./include/headers",
        "./dependencies/SDL2/include",
        "./dependencies/glew-2.2.0/include",
        "./dependencies/freeglut/include"
    }
    
    vpaths {
        ["Headers"] = { 
            "./include/headers",
            "./dependencies/SDL2/include",
            "./dependencies/glew-2.2.0/include",
            "./dependencies/freeglut/include",
            -- Add any additional include directories here
        }
    }
 
    
    --Include directories
    includedirs {
        "./include/headers",
        "./dependencies/SDL2/include",
        "./dependencies/glew-2.2.0/include",
        "./dependencies/freeglut/include"
    }

    --libraries and links
        --links (the library files)
        links {
            "SDL2",
            "SDL2main",
            "SDL2test",
            "opengl32",
            "user32",
            "gdi32",
            "shell32",
            "glew32s",
            "glew32",
            "freeglut"
        }

        --for 32 bit use these library paths
        filter "architecture:x86"
            libdirs { 
                "./dependencies/SDL2/lib/x86",
                "./dependencies/glew-2.2.0/lib/Release/Win32",
                "./dependencies/freeglut/lib"
             }
            syslibdirs {   
                "./dependencies/SDL2/lib/x86",
                "./dependencies/glew-2.2.0/lib/Release/Win32",
                "./dependencies/freeglut/lib"
            }
            
        filter { }
        --for x64 use these
        filter "architecture:x64"
            libdirs { 
                "./dependencies/SDL2/lib/x64",
                "./dependencies/glew-2.2.0/lib/Release/x64",
                "./dependencies/freeglut/lib/x64"
            }
            syslibdirs { 
                "./dependencies/SDL2/lib/x64",
                "./dependencies/glew-2.2.0/lib/Release/x64",
                "./dependencies/freeglut/lib/x64"
            }
    
    --Debug and Release configurations
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { }