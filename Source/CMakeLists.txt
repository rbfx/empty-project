# Include source files.
set (SOURCE_FILES Main.cpp)

# Windows only: URHO3D_WIN32_CONSOLE controls whether to keep console or not
if (NOT URHO3D_WIN32_CONSOLE)
    set (PLATFORM WIN32)
endif ()

# Add executable.
set (TARGET_NAME ${CMAKE_PROJECT_NAME})
add_executable(${TARGET_NAME} ${PLATFORM} ${SOURCE_FILES})

# Link the engine and plugins.
target_link_libraries (${TARGET_NAME} PRIVATE
    Urho3D
    Plugin.Core.SamplePlugin
)
