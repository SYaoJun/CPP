cmake_minimum_required(VERSION 3.15)
project(hpc)
set(CMAKE_CXX_STANDARD 17)

###########################################
# version 1
###########################################
include_directories(/opt/homebrew/Cellar/tbb/2021.11.0/include)
find_library(TBB_LIBS tbb /opt/homebrew/Cellar/tbb/2021.11.0/lib)
add_executable(find_prime find_prime.cc)

target_link_libraries(find_prime ${TBB_LIBS})
###########################################
# version 2
###########################################
# find_package(TBB REQUIRED)
# include_directories(TBB_INCLUDE_DIRS)
# add_executable(find_prime find_prime.cc)
# target_link_libraries(find_prime ${TBB_LIBRARIES})
