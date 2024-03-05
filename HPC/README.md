# TBB
## install
```c
brew install tbb
```
## CMakeLists.txt
- We should give the header path
- We need to give the library path
```c
cmake_minimum_required(VERSION 3.15)
project(hpc)
set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/Cellar/tbb/2021.11.0/include)
find_library(TBB_LIBS tbb /opt/homebrew/Cellar/tbb/2021.11.0/lib)
add_executable(find_prime find_prime.cc)

target_link_libraries(find_prime ${TBB_LIBS})
```