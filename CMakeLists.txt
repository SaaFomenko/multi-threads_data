cmake_minimum_required(VERSION 3.18)

project(multi-threads_data:)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${PROJECT_NAME}.exe main.cpp)
