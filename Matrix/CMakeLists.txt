cmake_minimum_required(VERSION 3.15)
project(hpc)
set(CMAKE_CXX_STANDARD 17)

# google test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://gitee.com/mirrors/googletest
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_test matrix_test.cpp)
# link static library
target_link_libraries(matrix_test gtest_main)

