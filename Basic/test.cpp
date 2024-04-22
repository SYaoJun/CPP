// test.cpp 
// 打印lzma库的版本号
// g++ -o test test.cpp `pkg-config --cflags --libs liblzma`
#include "lzma.h"
#include <iostream>

int main(int argc, char** argv)
{
    const char* version = lzma_version_string();
    std::cout << "lzma version is: " << version << std::endl;
    return 0;
}