#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mutex;
    static std::once_flag co;
    Singleton() {
        // 私有构造函数
    }
public:
    void doSomething() {
        // 执行一些操作
        std::cout << "Singleton is doing something." << std::endl;
    }

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        std::call_once(co, [&]{ instance = new Singleton();});
        return instance;
    }
};
Singleton* Singleton::instance(nullptr);
std::mutex Singleton::mutex;
std::once_flag Singleton::co;
int main(){
    Singleton* singleton1 = Singleton::getInstance();
    singleton1->doSomething();

    Singleton* singleton2 = Singleton::getInstance();
    singleton2->doSomething();

    return 0;
}