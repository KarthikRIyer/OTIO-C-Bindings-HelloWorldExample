cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project(otio_hello_world VERSION 1.0.0 LANGUAGES CXX C)

set(COTIO_INSTALL OFF)
set(COTIO_SHARED_LIBS OFF)

add_subdirectory(OpenTimelineIO-C-Bindings)
add_subdirectory(src)