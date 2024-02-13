cmake_minimum_required(VERSION 3.14)
project (EmptyProject)

# C++17 is required for this project.
set (CMAKE_CXX_STANDARD 17)

# Setup output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# It is possible to use pre-built SDK or build the Framework from source.
# In your project, you can choose either option or keep both.
set (REBELFORK_SDK "" CACHE STRING "Path to pre-built SDK")
if ("${REBELFORK_SDK}" STREQUAL "")
    # Include common build scripts.
    include (${CMAKE_SOURCE_DIR}/../rbfx/CMake/Modules/UrhoCommon.cmake)

    # Include the Framework to build.
    add_subdirectory (../rbfx ${CMAKE_BINARY_DIR}/3rdParty/rbfx)
else ()
    # Include common build scripts.
    include (${REBELFORK_SDK}/share/CMake/Modules/UrhoCommon.cmake)

    # Include pre-built SDK
    set (CMAKE_PREFIX_PATH ${REBELFORK_SDK}/share)
    find_package(Urho3D REQUIRED)
endif ()

# Add plugins (optional).
include_directories (${CMAKE_SOURCE_DIR}/Plugins)
add_subdirectory (${CMAKE_SOURCE_DIR}/Plugins/Core.SamplePlugin)

# Add project source files.
add_subdirectory (${CMAKE_SOURCE_DIR}/Source)
