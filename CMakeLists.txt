cmake_minimum_required(VERSION 3.20)
project(NeonDreams)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# TODO: Windows implementation
# TODO: Remove hard-coded paths like `/usr/include` or `/opt/homebrew/include`

# Compiler flags
add_compile_options(
    -Wall
    -Werror
    -O2
    -flto
    -funroll-loops
    -ffast-math
)

# Unix & not Apple => Linux
if(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux...")
    include_directories(
        /usr/include
        /usr/include/SDL2
        /usr/include/nlohmann
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
    )

    set(SYSTEM_LIBS
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        GL
    )

# MacOS for Apple Silicon
# Intel Macs are not in support right now
elseif(APPLE)
    message(STATUS "Configuring for macOS")
    include_directories(
        /opt/homebrew/include
        /opt/homebrew/include/SDL2
        /opt/homebrew/include/nlohmann
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
    )

    link_directories(/opt/homebrew/lib)

    set(SYSTEM_LIBS
        SDL2
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        "-framework OpenGL"
    )
endif()

# MRuby includes
include_directories(${CMAKE_SOURCE_DIR}/external/mruby/include)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/include/*.hpp
    ${CMAKE_SOURCE_DIR}/include/*.h
)

# ImGui sources
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
)

# Executable
add_executable(NeonDreams ${SOURCES} ${HEADERS} ${IMGUI_SOURCES})

# Link system libs + MRuby static lib
target_link_libraries(NeonDreams
    ${SYSTEM_LIBS}
    ${CMAKE_SOURCE_DIR}/external/mruby/build/host/lib/libmruby.a
)

# Output directory
set_target_properties(NeonDreams PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "NeonDreams has been compiled with all dependencies.")
message(STATUS "Remember to compile mruby before running!")
