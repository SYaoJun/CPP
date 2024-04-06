#include <iostream>
#include <thread>

class MyThread {
public:
    MyThread() {
        // 在构造函数中创建线程
        thread_ = std::thread(&MyThread::threadFunction, this);
    }

    ~MyThread() {
        if (thread_.joinable()) {
            thread_.join(); // 在析构函数中等待线程结束
        }
    }

    void threadFunction() {
        // 线程函数
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread is running... " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    std::thread thread_;
};

int main() {
    MyThread myThread; // 创建 MyThread 对象，启动线程

    // 做一些其他的事情...

    return 0;
}
