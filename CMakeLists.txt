cmake_minimum_required(VERSION 3.28)

project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RPS)

set(INCLUDES
        include/RPS/Sort.h
        include/RPS/Random.h
        include/RPS/Concepts.h
        include/RPS/IO/File.h
        include/RPS/IO/Console.h)

set(SOURCE
        src/main.cpp)

target_sources(RPS
        PRIVATE ${SOURCE}
        PUBLIC FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}
        FILES ${INCLUDES})

target_include_directories(RPS PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")