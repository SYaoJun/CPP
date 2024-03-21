cmake_minimum_required(VERSION 3.15)
project(mpmc)
set(CMAKE_CXX_STANDARD 17)
add_executable(paxos disk_paxos.cpp)