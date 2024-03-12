cmake_minimum_required(VERSION 3.12)
project(lz4_project)

set(CMAKE_CXX_STANDARD 11)

add_executable(lz4_exe lz4.cpp)
# cmake default search path for external libraries
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(LZ4 REQUIRED)

if(LZ4_FOUND)
    target_include_directories(lz4_exe PRIVATE ${LZ4_INCLUDE_DIR})
    target_link_libraries(lz4_exe PRIVATE ${LZ4_LIBRARY})
else()
    message(FATAL_ERROR "LZ4 library not found.")
endif()
