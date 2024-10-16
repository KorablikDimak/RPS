cmake_minimum_required(VERSION 3.28)

project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ExtendedCPP REQUIRED)
find_package(libpqxx REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS HttpServer Widgets)
qt_standard_project_setup()

set(WebApi_INCLUDES
        include/RPS/WebApi/Api.h
        include/RPS/WebApi/DbPool.h
        include/RPS/WebApi/DbProvider.h
        include/RPS/WebApi/DbMacros.h
        include/RPS/WebApi/DataContext.h
        include/RPS/WebApi/DbArray.h
        include/RPS/WebApi/DbUtility.h
        include/RPS/WebApi/Storage.h)

set(WebApi_SOURCE
        src/WebApi/main.cpp
        src/WebApi/Api.cpp
        src/WebApi/DbPool.cpp
        src/WebApi/DataContext.cpp
        src/WebApi/Storage.cpp)

qt_add_executable(WebApi ${WebApi_INCLUDES} ${WebApi_SOURCE})
target_link_libraries(WebApi PRIVATE Qt6::HttpServer libpqxx::pqxx ExtendedCpp::LINQ ExtendedCpp::Json ExtendedCpp::DI)

target_include_directories(WebApi PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

if(APPLE)
    set_target_properties(WebApi PROPERTIES
            MACOSX_BUNDLE ON)

    add_custom_command(
            TARGET WebApi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/variables.json
            ${CMAKE_CURRENT_BINARY_DIR}/WebApi.app/Contents/MacOS/variables.json)
else()
    add_custom_command(
            TARGET WebApi POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/variables.json
            ${CMAKE_CURRENT_BINARY_DIR}/variables.json)
endif()

set(Application_INCLUDES
        include/RPS/Application/MainWindow.h)

set(Application_SOURCE
        src/Application/MainWindow.cpp
        src/Application/main.cpp)

set(Application_UI
        src/Application/MainWindow.ui)

qt_add_executable(Application ${Application_INCLUDES} ${Application_SOURCE} ${Application_UI})
target_link_libraries(Application PRIVATE Qt6::Widgets)

target_include_directories(Application PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

if(APPLE)
    set_target_properties(Application PROPERTIES
            MACOSX_BUNDLE ON)
endif()