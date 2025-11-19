
cmake_minimum_required(VERSION 3.10)
project(RonnyShrine)

set(CMAKE_CXX_STANDARD 17)

# Add your source files
add_executable(RonnyShrine
    main.cpp
    include/texture.cpp
    glad.c
    shape.cpp
    # ImGui core
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    # ImGui backends
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
)

# Include directories
target_include_directories(RonnyShrine PRIVATE
    include
    imgui
)

# Find and link GLFW + OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(RonnyShrine PRIVATE glfw OpenGL::GL)
