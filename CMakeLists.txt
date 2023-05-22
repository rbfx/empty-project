cmake_minimum_required(VERSION 3.14)
project (EmptyProject)

# C++17 is required for this project.
set (CMAKE_CXX_STANDARD 17)

# Setup output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include common build scripts.
include (${CMAKE_SOURCE_DIR}/../rbfx/CMake/Modules/UrhoCommon.cmake)

# Include the Framework.
add_subdirectory (../rbfx ${CMAKE_BINARY_DIR}/3rdParty/rbfx)

# Add project source files.
add_subdirectory (${CMAKE_SOURCE_DIR}/Source)
