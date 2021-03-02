cmake_minimum_required(VERSION 3.15)

find_program(CONAN conan)
if(NOT CONAN)
  message(WARNING "Conan not found. Skipping tests")
  return()
endif()

# if built within conan use the file from local cache
if(CONAN_EXPORTED)
  include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
else()
  # setting up conan to download.cmake automatically, you can also just copy the
  if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
    message(
      STATUS
        "Downloading conan.cmake from https://github.com/bernedom/cmake-conan")
    file(
      DOWNLOAD
      "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.15/conan.cmake"
      "${CMAKE_CURRENT_BINARY_DIR}/conan.cmake")
  endif()
  include(${CMAKE_CURRENT_BINARY_DIR}/conan.cmake)
  conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP
  CMAKE_TARGETS
  BUILD
  missing)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})

find_package(Catch2 REQUIRED)

add_executable(Patterno_unit_tests)
target_sources(
  Patterno_unit_tests
  PRIVATE src/Catch2Main.cc
          src/base_unit_tests/singleton.cc)

target_include_directories(
  Patterno_unit_tests PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

target_compile_features(Patterno_unit_tests PRIVATE cxx_std_17)
target_link_libraries(Patterno_unit_tests Catch2::Catch2)

target_compile_options(
  Patterno_unit_tests
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/std:c++17>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<CXX_COMPILER_ID:MSVC>:/WX>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wall>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Werror>
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-pedantic>
)

add_test(NAME Patterno_unit_tests COMMAND Patterno_unit_tests)