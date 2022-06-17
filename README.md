# A Simple Snake Game
This project is a simple implementation of the classic snake game made with the [SDL2 library](https://libsdl.org) in C++.

# Compiling from Source
The project uses [CMake](https://cmake.org) as the orchestrator of build systems. By default, it invokes the [Ninja build system](https://ninja-build.org) on top of the [Clang/LLVM](https://clang.llvm.org) compiler to build the project. Binaries are then saved in the `build` directory.

Package managers (such as [vcpkg](https://vcpkg.io/en/index.html) and [Conan](https://conan.io)) are not required. As long as CMake is able to resolve the following dependencies via [`find_package`](https://cmake.org/cmake/help/latest/command/find_package.html), the project should compile successfully:

* [SDL](https://github.com/libsdl-org/SDL)
* [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
* [PCG Random](https://github.com/imneme/pcg-cpp)

In order to make the most out of modern C++, the project also requires a compiler that supports C++20 (at least partially). Older versions are not supported to keep the project configuration simple.

```bash
# Clone the repository and its submodules
git clone --recursive https://github.com/Some-Dood/sdl-basic-snake.git

# Configure the CMake project using the default Ninja + Clang stack
cmake --preset=ninja -DSDL2_PATH=/path/to/sdl2 -DSDL2_TTF_PATH=/path/to/sdl2_ttf -DPCG_CPP_PATH=/path/to/pcg-cpp

# Build the project using the default preset
cmake --build build --config Release

# Run the project (in Windows for example) using a specific font
./build/Release/Snake.exe /path/to/some/font.ttf
```
