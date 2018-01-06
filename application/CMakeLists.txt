cmake_minimum_required(VERSION 3.9)
project(VideoPlayerApplication)

set(CMAKE_CXX_STANDARD 17)

set(
        VP_SOURCES
        src/Application.cpp include/Application.hpp
)

add_library(VideoPlayerApplication ${VP_SOURCES})

target_include_directories(VideoPlayerApplication PUBLIC include)
target_include_directories(VideoPlayerApplication PRIVATE src)


target_link_libraries(
        VideoPlayerApplication
        core base
)
target_link_libraries(
        VideoPlayerApplication
        VideoPlayerPlayer
)