# A Simple Snake Game
This project is a simple implementation of the classic snake game made with the [SDL2 library](https://libsdl.org) in C++.

# Compiling from Source
To simplify dependency management, this project uses [vcpkg][vcpkg] as its package manager. But, since we internally use [CMake][cmake] to orchestrate the build systems, package managers (e.g. [vcpkg][vcpkg] and [Conan][conan]) are technically not necessary. That is, as long as CMake is able to resolve the following dependencies via [`find_package`](https://cmake.org/cmake/help/latest/command/find_package.html), the project should compile successfully.

[cmake]: https://cmake.org
[vcpkg]: https://vcpkg.io/en/index.html
[conan]: https://conan.io

* [SDL](https://github.com/libsdl-org/SDL)
* [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
* [PCG Random](https://github.com/imneme/pcg-cpp)

In the preset configurations, CMake invokes the [Ninja build system](https://ninja-build.org) on top of the [Clang/LLVM](https://clang.llvm.org) compiler to build the project (by default). Binaries are then saved in the `build` directory. Of course, this configuration is workflow-specific. Feel free to use other compilers and build systems (supported by CMake). However, in order to make the most out of modern C++, the project requires a compiler that supports C++20 (at least partially). Older versions are not supported to keep the project configuration simple.

```bash
# Clone the repository and its submodules
git clone https://github.com/Some-Dood/sdl-basic-snake.git

# Configure the CMake project using the default Ninja + Clang stack
cmake --preset=ninja -DCMAKE_TOOLCHAIN_FILE=/path/to/scripts/buildsystems/vcpkg.cmake

# Build the project
cmake --build build --config Release

# Run the project (in Windows for example) using a specific font
./build/Release/Snake.exe /path/to/some/font.ttf
```
