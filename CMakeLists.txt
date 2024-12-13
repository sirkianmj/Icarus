cmake_minimum_required(VERSION 3.10)
project(IcarusCore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the policy for finding packages
cmake_policy(SET CMP0074 NEW)

# Set SFML root directory (adjust if necessary)
set(SFML_DIR "F:/IcarusDepn/SFML-2.6.2/lib/cmake/SFML")

# Find SFML package
find_package(SFML 2.6.2 COMPONENTS system window graphics REQUIRED)

# Add source files manually
set(SOURCES
        src/Window.cpp
        src/main.cpp
        include/GameObject.h
        src/GameObject.cpp
        include/Camera.h
        src/Camera.cpp
        include/ShaderUtils.h
        src/ShadeUtils.cpp
        # Add other source files here as needed
)

# Create an executable from the source files
add_executable(IcarusCore ${SOURCES})

# Set include directories directly for the target
target_include_directories(IcarusCore PRIVATE
        ${PROJECT_SOURCE_DIR}/include           # Your project header files
        ${PROJECT_SOURCE_DIR}/libs/glm         # GLM header files
        ${PROJECT_SOURCE_DIR}/libs/glew/include # GLEW header files
        F:/IcarusDepn/SFML-2.6.2/include       # SFML header files
)

# Link SFML libraries
target_link_libraries(IcarusCore
        sfml-system
        sfml-window
        sfml-graphics
)

# Link GLEW (64-bit version) - adjust the path if needed
target_link_libraries(IcarusCore
        F:/Icarus/libs/glew/lib/Release/x64/glew32.lib
)

# Link OpenGL (likely redundant if you're using sfml-window, but included for completeness)
find_package(OpenGL REQUIRED)
target_link_libraries(IcarusCore OpenGL::GL)

# Define shader source and destination paths
set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/Shaders")
set(SHADER_DEST_DIR "${CMAKE_BINARY_DIR}")  # Just the build directory, no need for 'cmake-build-debug'

# Add a custom command to copy the shaders
add_custom_command(TARGET IcarusCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADER_SOURCE_DIR} ${SHADER_DEST_DIR}/shaders
        COMMENT "Copying shader files to build directory"
)
