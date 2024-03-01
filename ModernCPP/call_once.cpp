#include <iostream>
#include <mutex>
#include <thread>
std::once_flag flag;

void initializeResource() {
    std::cout << "Resource initialized." << std::endl;
    // 进行初始化工作
}

void doSomething() {
    std::call_once(flag, initializeResource);
    // 在这里可以安全地使用已初始化的资源
    std::cout << "Doing something with the resource." << std::endl;
}

int main() {
    std::thread t1(doSomething);
    std::thread t2(doSomething);

    t1.join();
    t2.join();

    return 0;
}
