cmake_minimum_required(VERSION 3.15)

project("Patterno"
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "A header-only C++ library that provides support for using Design Patterns in your codebase.")

set(PROJECT_NAMESPACE "pat")

option(ENABLE_TESTING "Enable Test Builds" ON)

include(cmake/Conan.cmake)
run_conan()

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION include)

if(ENABLE_TESTING)
    enable_testing()
    message("Building Tests. Be sure to check out test/constexpr_tests for constexpr testing")
    add_subdirectory(test)
endif()
