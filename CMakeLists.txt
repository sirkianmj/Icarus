cmake_minimum_required(VERSION 3.10)
project(IcarusCore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify the directories for header files
include_directories(include)

# Set SFML directory (adjust if necessary)
set(SFML_DIR "F:/IcarusDepn/SFML-2.6.2/lib/cmake/SFML")

# Find SFML package
find_package(SFML 2.6.2 COMPONENTS system window graphics REQUIRED)

# Find all .cpp files in the src/ directory and store them in SOURCES
file(GLOB SOURCES "src/*.cpp")

# Create an executable and link the source files
add_executable(IcarusCore ${SOURCES})

# Link SFML libraries (no need to manually link directories)
target_link_libraries(IcarusCore sfml-system sfml-window sfml-graphics)
