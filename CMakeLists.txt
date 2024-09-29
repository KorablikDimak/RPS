cmake_minimum_required(VERSION 3.29)

project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES
        include/RPS/IO.h
        include/RPS/Sort.h
        include/RPS/Random.h
        include/RPS/Concepts.h
        include/RPS/IO/IReader.h
        include/RPS/IO/IWriter.h
        include/RPS/IO/FileReader.h
        include/RPS/IO/FileWriter.h
        include/RPS/IO/RandomReader.h)

set(SOURCE
        src/main.cpp)

add_executable(RPS ${INCLUDES} ${SOURCE})