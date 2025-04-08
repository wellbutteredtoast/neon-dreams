cmake_minimum_required(VERSION 3.20)
project(NeonDreams)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Compiler flags
add_compile_options(
    -Wall
    -Werror
    -O2
    -flto
    -funroll-loops
)

# System-wide includes
include_directories(
    /usr/include
    /usr/include/SDL2
    /usr/include/nlohmann
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends
)

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

# ImGui files
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
)

# Executable
add_executable(NeonDreams ${SOURCES} ${HEADERS} ${IMGUI_SOURCES})

# Link system + mruby
target_link_libraries(NeonDreams
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
    GL
    m
    ${CMAKE_SOURCE_DIR}/external/mruby/build/host/lib/libmruby.a
)

# Output location
set_target_properties(NeonDreams PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(STATUS "NeonDreams configured with SDL2 + OpenGL + ImGui + JSON + MRuby")
