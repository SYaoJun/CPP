#include <iostream>
#include <string.h>
class A{

private:
    char* data;
public:
    A(char* data_): data(data_){}
// 移动构造
    A(A&& other){
        std::cout << "移动构造函数被调用" << std::endl;
        data = other.data;
        other.data = nullptr;  // 防止其他对象释放相同的资源
    }
// 移动拷贝
    A& operator=(A&& other){
        // 这个other不用析构吗？
        std::cout << "移动赋值运算符被调用" << std::endl;
        if (this != &other) {
            delete[] data;  // 释放当前对象的资源

            data = other.data;  // 移动资源所有权
            other.data = nullptr;  // 防止其他对象释放相同的资源
        }
        return *this;
    }
    void show(){
        std::cout<<data<<std::endl;
    }
};

int main(){
    char *x = (char*)malloc(sizeof(char)*100);
    strcpy(x, "hello world");
    A a(x);
    A b = std::move(a); // move constructor
    A c(x);
    c = std::move(b); // move assignment
    c.show();
}