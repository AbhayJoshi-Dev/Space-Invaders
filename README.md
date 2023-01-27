# Space Invaders

A clone of Space Invaders created using C++ and [SDL2](https://www.libsdl.org/)

## Demo
![](https://i.imgur.com/NTygwuY.gif)

## Build Instructions

- Requirements
  - Git
  - CMake
  - C++ Compiler

- Steps

    ```cmd
    # Clone this project along with submodules
    $ git clone --recursive https://github.com/AbhayJoshi-Dev/Space-Invaders

    # Go to project root
    $ cd Space-Invaders

    # Pull SDL and SDL_image as submodule (if you cloned without --recursive flag)
    $ git submodule update --init

    # Create a folder for build
    $ mkdir build

    # Go to build folder
    $ cd build

    # Generate project files
    $ cmake ..
    ```

- This will generate project files using default cmake generator for your platform. For example:

  - on `Windows` with `Visual Studio` installed, it will generate a `.sln`
  - on `Linux` with `make` installed, it will generate a `Makefile`
  - on `Mac` with `xcode` installed, it will generate a `.xcodeproj`
  