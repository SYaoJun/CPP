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

int main() {
    
    std::cout << "Hello from the main thread" << std::endl;

    int n = 100000;

    std::vector<std::thread> threads;
    for(int i = 0; i < n; i++){
        threads.emplace_back(threadFunction, i);
    }
    for(int i = 0; i < n; i++) {
        threads[i].join();
    }
    std::cout<<counter<<std::endl;
    return 0;
}
