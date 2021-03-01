add_executable(test_main main.cpp)

set_property(TARGET test_main PROPERTY CXX_STANDARD 17)
set_property(TARGET test_main PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(test_main PUBLIC CONAN_PKG::catch2)
target_include_directories(test_main PRIVATE ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})

include(CTest)
include(Catch)

catch_discover_tests(test_main)
enable_testing()