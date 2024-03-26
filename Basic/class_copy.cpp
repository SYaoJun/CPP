#include <iostream>
#include <string.h>
class A{

private:
    char* data;
public:
    A(char* data_): data(data_){}
    A(const A& other){
        std::cout << "copy constructor" << std::endl;
        data = other.data;
    }
    A& operator=(const A& other){
        std::cout << "copy assignment" << std::endl;
        if (this != &other) {
            data = other.data;  
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
    A b = std::move(a); // copy constructor
    A c(x);
    c = std::move(b); // copy assignment
    c.show();
}