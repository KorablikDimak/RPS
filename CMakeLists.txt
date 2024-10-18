cmake_minimum_required(VERSION 3.28)

project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEPLOY_QT OFF)

find_package(ExtendedCPP REQUIRED)
find_package(libpqxx REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core HttpServer Widgets)
qt_standard_project_setup()

include(cmake/utils.cmake)

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

if(APPLE)
    target_link_options(WebApi PRIVATE -framework CoreFoundation)
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

set_private_include_directories(WebApi Application)
set_platform_properties(WebApi Application)

if(DEPLOY_QT)
    deploy_qt(WebApi Application)
endif()