####################################### Enforce CMake Version

cmake_minimum_required(VERSION 3.20)

####################################### Project definition

project(PrincessVS_Tools VERSION 0.0.1 DESCRIPTION "Princess VS Tools" LANGUAGES CXX)

####################################### Enforcing C++20 standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

####################################### Find All Source Files

file(
    GLOB_RECURSE
    PRINCESS_VS_SOURCES
    CONFIGURE_DEPENDS
    "src/*.cpp"
    "include/*.h"
)

####################################### Executable Targets

add_executable(
    ${PROJECT_NAME} 
    ${PRINCESS_VS_SOURCES}
)

# Specify include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC 

    include/
    "${PROJECT_SOURCE_DIR}/deps/vulkan/include/vulkan" #vulkan uwu
    "${PROJECT_SOURCE_DIR}/deps/vulkan/include/spirv-headers"

    "${PROJECT_SOURCE_DIR}/deps/header_only"
)

####################################### Static Imports

if(WIN32 )

    add_library(python313 STATIC IMPORTED)

    set_target_properties(python313 PROPERTIES
        IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/python/winx64/python313.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/python/winx64/include"
    )

        ############ Vulkan Specific Imports

        add_library(shaderC STATIC IMPORTED)

        set_target_properties(shaderC PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/vulkan/winx64/shaderc.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/vulkan/include/shaderc"
        )

        add_library(volk STATIC IMPORTED)
    
        set_target_properties(volk PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/vulkan/winx64/volk.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/vulkan/include/Volk"
        )
    
        add_library(SPIRV_Tools STATIC IMPORTED)
    
        set_target_properties(SPIRV_Tools PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/vulkan/winx64/SPIRV-Tools.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/vulkan/include/spirv-tools"
        )
    
        add_library(SPIRV_Cross STATIC IMPORTED)
    
        set_target_properties(SPIRV_Cross PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/vulkan/winx64/spirv-cross-c.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/vulkan/include/spirv_cross"
        )

        add_library(SDL3 STATIC IMPORTED)

        set_target_properties(SDL3 PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/SDL3/winx64/SDL3-static.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/SDL3/include"
        )

        add_library(PhysFS STATIC IMPORTED)

        set_target_properties(PhysFS PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/physfs/winx64/physfs-static.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/physfs/include"
        )

elseif(APPLE)

        add_library(python313 STATIC IMPORTED)
    
        set_target_properties(python313 PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/python/osxARM64/python313.a"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/python/osxARM64/include"
        )

        add_library(SDL3 SHARED IMPORTED)

        set_target_properties(SDL3 PROPERTIES
            IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/SDL3/osxARM64/libSDL3.0.dylib"
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/SDL3/include"
        )

elseif(UNIX) #XXX: doing these later when i compile on my linux machine
        message(FATAL_ERROR "nothing for unix/linux just yet oof >w<")
    
        # add_library(python313 STATIC IMPORTED)
    
        # set_target_properties(python313 PROPERTIES
        #     IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/deps/python/lib_winx86/python313.lib"
        #     INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/deps/python/include_winx86"
        # )

else()
    message(FATAL_ERROR "UNSUPPORTED PLATFORM PEACH_ENGINE IS ONLY SUPPORTED ON WINDOWS/OSX/LINUX SORRY NOT SORRY")

endif()


####################################### Dependency Linking

if(APPLE ) #link moltenVK for mac compatibility
    target_link_libraries(${PROJECT_NAME} PUBLIC
        moltenVK
    )
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    python313
    shaderC
    volk
    SPIRV_Tools
    SPIRV_Cross

    SDL3
    PhysFS
)

####################################### Set Startup Project (Visual Studio & Xcode)


# Set Peach_Editor as the startup project for Visual Studio

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    message(STATUS "Setting ${PROJECT_NAME} as the default startup project for VS2022")
endif()