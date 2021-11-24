cmake_minimum_required(VERSION 3.19)

project(Snake)
add_executable(
    ${PROJECT_NAME}
    src/Main.cpp
    src/SDL/Context.cpp
    src/SDL/Surface.cpp
    src/SDL/Texture.cpp
    src/SDL/Renderer.cpp
    src/SDL/Window.cpp
    src/TTF/Context.cpp
    src/TTF/Font.cpp
    src/Game/Scene.cpp
)

# Include Directories
target_include_directories(${PROJECT_NAME} PUBLIC deps/sdl2/include)
target_include_directories(${PROJECT_NAME} PUBLIC deps/ttf/include)

# Link Directories
target_link_directories(${PROJECT_NAME} PUBLIC deps/sdl2/lib/x64)
target_link_directories(${PROJECT_NAME} PUBLIC deps/ttf/lib/x64)

# Static Libraries
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_ttf)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} Shell32)
endif()

# C++ Configuration
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC
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
