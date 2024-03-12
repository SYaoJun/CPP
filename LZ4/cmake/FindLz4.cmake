# provide header path and library path
# if you want to run you own code, you had better change to your lz4 install path
find_path(LZ4_INCLUDE_DIR lz4.h /opt/homebrew/Cellar/lz4/1.9.4/include ${CMAKE_SOURCE_DIR}/ModuleMode)
find_library(LZ4_LIBRARY NAMES lz4 PATHS  /opt/homebrew/Cellar/lz4/1.9.4/lib ${CMAKE_SOURCE_DIR}/ModuleMode)

message(STATUS "enter cmake directory!")
if (LZ4_INCLUDE_DIR AND LZ4_LIBRARY)
    set(LZ4_FOUND TRUE)
endif (LZ4_INCLUDE_DIR AND LZ4_LIBRARY)