cmake_minimum_required(VERSION 3.14)
project (EmptyProject)

# C++17 is required for this project.
set (CMAKE_CXX_STANDARD 17)

# Setup output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Engine must be available on CMAKE_PREFIX_PATH:
# Option 1 - prebuilt SDK:
#   - Download a prebuilt SDK and extract it somewhere
#   - Configure with `-DCMAKE_PREFIX_PATH=/path/to/your/sdk -DCMAKE_CONFIGURATION_TYPES="Debug;RelWithDebInfo"`
#     - CMAKE_CONFIGURATION_TYPES may or may not be necessary, depending on your SDK configuration
# Option 2 - in-source build:
#   - Clone https://github.com/rbfx/rbfx somewhere
#   - Configure with `-DCMAKE_PREFIX_PATH=/path/to/rbfx/CMake`
find_package(Urho3D REQUIRED)

# Add plugins (optional).
include_directories (${CMAKE_SOURCE_DIR}/Plugins)
add_subdirectory (${CMAKE_SOURCE_DIR}/Plugins/Core.SamplePlugin)

# Add project source files.
add_subdirectory (${CMAKE_SOURCE_DIR}/Source)
