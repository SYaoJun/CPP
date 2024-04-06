#include <iostream>
#include <thread>
#include <mutex>
int counter = 0;
std::mutex mtx;
// 线程函数
void threadFunction(int threadID) {
    std::lock_guard<std::mutex> lg(mtx);
    counter++;
    // std::cout << "Hello from thread " << threadID << std::endl;
}

void thread_func(int id){
    std::cout<<"thread run..."<<id<<std::endl;
}
int main() {
    
    std::cout << "Hello from the main thread" << std::endl;

    // int n = 1;

    // std::vector<std::thread> threads;
    // for(int i = 0; i < n; i++){
    //     threads.emplace_back(threadFunction, i);
    // }
    // for(int i = 0; i < n; i++) {
    //     threads[i].join();
    // }
    // std::cout<<counter<<std::endl;
    // 线程是一个类
    // 1. 列表初始化
    // 2. 传统方式调用构造函数
    std::thread t1{thread_func, 109};
    std::thread t2(thread_func, 200);
    t1.join();
    t2.join();
    std::optional<std::thread> background_thread_;
    // std::thread t3(thread_func, 2000);
    background_thread_.emplace(thread_func, 200);
    if(background_thread_.has_value()){
        background_thread_.value().join();
    }
    return 0;
}
