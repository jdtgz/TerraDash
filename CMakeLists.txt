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

add_executable(main 
    src/main.cpp
    src/Game.cpp
    "src/Game Elements/Level.cpp"
    "src/Game Elements/Player.cpp"
    src/Graphics/Animation.cpp
    src/Graphics/Resources.cpp

    )
target_include_directories(main PRIVATE ${box2d_SOURCE_DIR}/include)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics box2d)
