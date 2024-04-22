cmake_minimum_required(VERSION 3.12)
project(lz4_project)
// pkg-config --list-all | grep lz4 如果能直接搜索到 那么就不需要设置专属路径去查找了
set(CMAKE_CXX_STANDARD 11)

add_executable(lz4_exe lz4.cpp)
# SET(ENV{PKG_CONFIG_PATH} /opt/homebrew/Cellar/lz4/1.9.4/lib/pkgconfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(MYLZ4 REQUIRED IMPORTED_TARGET liblz4)

if(MYLZ4_FOUND)
    target_link_libraries(lz4_exe PRIVATE PkgConfig::MYLZ4)
else()
    message(FATAL_ERROR "LZ4 library not found.")
endif()
