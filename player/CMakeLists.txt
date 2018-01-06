cmake_minimum_required(VERSION 3.9)
project(VideoPlayerPlayer)

set(CMAKE_CXX_STANDARD 17)

set(
        VP_SOURCES
        include/OpenGL.h
        src/PlayerView.cpp include/PlayerView.hpp
        src/VideoDecoder.cpp include/VideoDecoder.hpp
        src/RenderCanvas.cpp include/RenderCanvas.hpp
)

add_library(VideoPlayerPlayer ${VP_SOURCES})

target_include_directories(VideoPlayerPlayer PUBLIC include)
target_include_directories(VideoPlayerPlayer PRIVATE src)


target_link_libraries(
        VideoPlayerPlayer
        core base gl media
)

message(STATUS "AV ${AV_INCLUDES} ${AV_LIBRARIES}")

target_include_directories(
        VideoPlayerPlayer
        PUBLIC
        ${AV_INCLUDES}
)

target_link_libraries(
        VideoPlayerPlayer
        ${AV_LIBRARIES}
)

message(STATUS "GLAD ${GLAD_INCLUDE_DIRS} ${GLAD_LIBRARIES}")

target_include_directories(
        VideoPlayerPlayer
        PUBLIC
        ${GLAD_INCLUDE_DIRS}
)

target_link_libraries(
        VideoPlayerPlayer
        ${GLAD_LIBRARIES}
)

target_include_directories(VideoPlayerPlayer PUBLIC ${CMAKE_SOURCE_DIR}/ext/glm/glm)
target_link_libraries(VideoPlayerPlayer glm_shared)