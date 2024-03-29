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
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::TTF)
target_include_directories(${PROJECT_NAME} PRIVATE ${PCG_CPP_PATH}/include)
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
