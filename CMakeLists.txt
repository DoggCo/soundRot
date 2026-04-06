cmake_minimum_required(VERSION 3.10)
project(soundRot)

set(CMAKE_CXX_STANDARD 17)

# Add SoLoud
add_subdirectory(soloud)

add_executable(soundRot main.cpp)

# Link SoLoud
target_link_libraries(soundRot soloud)
