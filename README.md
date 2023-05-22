# Empty project

This is empty project that used [the Framework](https://github.com/rbfx/rbfx) as submodule.

It demonstrates the absolute minimum of code that is necessary to render something on the screen on Desktop platforms.

Mobile and Web platforms have their quirks and require additional code to work.

## Building the Project

1. Checkout [the Framework](https://github.com/rbfx/rbfx) as `rbfx` directory anywhere, if you didn't do that already.
2. Checkout this repository near `rbfx` directory.
3. Configure and build it via CMake. For example:

```
cd path/to/project
cmake . ./cmake-build
cmake --build ./cmake-build -j12
```

## Running the Sample

Just run `EmptyProject.exe` on Windows or `EmptyProject` on Linux.

Make sure that `rbfx/bin/CoreData` is visible by the executable.
It is usually copied automatically by CMake, but if it doesn't, you can copy it manually.

Alternatively, you can run `EmptyProject` executable with `--pp path/to/bin` command line argument
to specify the path to the directory containing `CoreData`.
