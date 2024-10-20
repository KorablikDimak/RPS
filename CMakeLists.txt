cmake_minimum_required(VERSION 3.28)

project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/utils.cmake)

if(APPLE)
    option(DEPLOY_APPLICATION "Deploy Application executable" OFF)
elseif(WIN32)
    option(DEPLOY_WEBAPI "Deploy WebApi executable" ON)
    option(DEPLOY_APPLICATION "Deploy Application executable" ON)
endif()
option(BUILD_TESTS "Build test" ON)

find_package(ExtendedCPP REQUIRED)
find_package(libpqxx REQUIRED)
find_package(GTest REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core HttpServer Widgets Network)
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
target_add_content(WebApi settings.json)
target_include_directories(WebApi PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/WebApi>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/WebApi>)
if(DEPLOY_WEBAPI)
    deploy_qt(WebApi)
endif()

set(Application_INCLUDES
        include/RPS/Application/Utility.h
        include/RPS/Application/MainWindow.h
        include/RPS/Application/EditArrayWindow.h
        include/RPS/Application/AddArrayWindow.h
        include/RPS/Application/Array.h
        include/RPS/Application/Repository.h
        include/RPS/Application/Storage.h)

set(Application_SOURCE
        src/Application/main.cpp
        src/Application/MainWindow.cpp
        src/Application/EditArrayWindow.cpp
        src/Application/Utility.cpp
        src/Application/AddArrayWindow.cpp
        src/Application/Storage.cpp)

set(Application_UI
        src/Application/MainWindow.ui
        src/Application/EditArrayWindow.ui
        src/Application/AddArrayWindow.ui)

if(APPLE)
    qt_add_executable(Application MACOSX_BUNDLE ${Application_INCLUDES} ${Application_SOURCE} ${Application_UI})
    target_link_options(WebApi PRIVATE -framework CoreFoundation)
elseif(WIN32)
    qt_add_executable(Application WIN32_EXECUTABLE ${Application_INCLUDES} ${Application_SOURCE} ${Application_UI})
endif()
target_link_libraries(Application PRIVATE Qt6::Widgets Qt6::Network ExtendedCpp::LINQ ExtendedCpp::Json)
target_add_content(Application settings.json)
target_include_directories(Application PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Application>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Application>)
if(DEPLOY_APPLICATION)
    deploy_qt(Application)
endif()

if(BUILD_TESTS)
    enable_testing()

    set(TESTS_INCLUDES
            include/RPS/WebApi/DbPool.h
            include/RPS/WebApi/DbProvider.h
            include/RPS/WebApi/DbMacros.h
            include/RPS/WebApi/DataContext.h
            include/RPS/WebApi/DbArray.h
            include/RPS/WebApi/DbUtility.h
            include/RPS/WebApi/Storage.h)

    set(TESTS_SOURCE
            src/WebApi/DbPool.cpp
            src/WebApi/DataContext.cpp
            src/WebApi/Storage.cpp
            tests/main.cpp
            tests/DatabaseTests.cpp)

    add_executable(Tests ${TESTS_INCLUDES} ${TESTS_SOURCE})
    target_link_libraries(Tests PRIVATE libpqxx::pqxx ExtendedCpp::LINQ ExtendedCpp::Common GTest::gtest GTest::gtest_main)
    target_add_content(Tests settings.json)
    target_include_directories(Tests PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tests>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/tests>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/WebApi>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/WebApi>)
endif()