#include <iostream>
#include <cstring>
int main(){
    const char* p = "  +123abc";
    const char* pp = "-123";
    long long t = atoll(p);
    long long tt = atoll(pp);
    // 如果失败返回0
    std::cout<<t<<std::endl;
    std::cout<<tt<<std::endl;
}