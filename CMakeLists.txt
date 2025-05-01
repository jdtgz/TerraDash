cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  Box2D
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v2.4.1
)
FetchContent_MakeAvailable(Box2D)

FetchContent_Declare(
        cpp-httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG        v0.20.0 # Use the desired version
)
FetchContent_MakeAvailable(cpp-httplib)

# Collect all .cpp files in src and its subdirectories
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Collect all .h files in include
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main ${SRC_FILES})

file(COPY ${CMAKE_SOURCE_DIR}/src/Textures DESTINATION ${CMAKE_BINARY_DIR}/bin/Debug)
target_include_directories(main PRIVATE ${box2d_SOURCE_DIR}/include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE 
  SFML::Graphics 
  box2d
  httplib::httplib
)
