# Space Invaders

A clone of [Space Invaders](https://en.wikipedia.org/wiki/Space_Invaders) written in C++ with [SDL2](https://www.libsdl.org/)

## Demo
![](https://i.imgur.com/PRZ4INP.gif)

## Build Instructions

- Requirements
  - Git
  - CMake
  - C++ Compiler

- Steps

    ```sh
    # Clone this project along with submodules
    git clone --recursive https://github.com/AbhayJoshi-Dev/Space-Invaders

    # Go to project root
    cd Space-Invaders

    # Create a folder for build
    mkdir build

    # Go to build folder
    cd build

    # Generate project files
    cmake .. # add -DBUILD_SHARED_LIBS=OFF to link statically

    # Build project
    cmake --build .
    ```
  