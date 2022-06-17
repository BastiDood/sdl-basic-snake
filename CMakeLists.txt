cmake_minimum_required(VERSION 3.19)

project(Snake)
add_executable(
    ${PROJECT_NAME}
    WIN32
    src/Main.cpp
    src/SDL/Context.cpp
    src/SDL/Surface.cpp
    src/SDL/Texture.cpp
    src/SDL/Renderer.cpp
    src/SDL/Window.cpp
    src/TTF/Context.cpp
    src/TTF/Font.cpp
    src/Game/Scene.cpp
    src/Game/Snake.cpp
)

# Dependency Resolution
find_package(SDL2 REQUIRED)
find_package(sdl2-ttf REQUIRED)
find_path(PCG_INCLUDE_DIRS "pcg_random.hpp")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
target_include_directories(${PROJECT_NAME} PRIVATE ${PCG_INCLUDE_DIRS})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE Shell32)
endif()

# C++ Configuration
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -pedantic
    -Wall
    -Wextra
    -Wshadow
    -Wunused
    -Wpadded
    -Wconversion
    -Wsign-conversion
    -Wdouble-promotion
    -Wnull-dereference
)
