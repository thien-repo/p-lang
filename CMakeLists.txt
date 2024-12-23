cmake_minimum_required(VERSION 3.16)

project(p-lang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES main.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(p ${SOURCES})