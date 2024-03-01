#include <iostream>
using namespace std;
class A{
public:
// 有虚函数
    virtual void func() const { cout<<"Class A"<<endl; }
private:
    int m_a;
};
class B: public A{
public:
// 重载虚函数
    virtual void func() const { cout<<"Class B"<<endl; }
private:
    int m_b;
};
int main(){
    // pa指向派生类B的指针
    A* pa = new B();
    // 父类转换为子类，但是父类必须是子类实例化的
    B* pb = dynamic_cast<B*>(pa);
    if(pb) {
        cout<<"cast success!"<<endl;
    }else{
        std::cout<<"cast failed!"<<std::endl;
    }
    return 0;
}