
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES x86_64)

project(easyUtils)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)

find_package(Threads)

option (BUILD_TESTS "Build test programs" OFF)

add_subdirectory(src)

if (${BUILD_TESTS})
    include_directories(subprojects/Catch2/single_include/catch2)
    add_subdirectory(test)
    add_subdirectory(demo)
endif (${BUILD_TESTS})
