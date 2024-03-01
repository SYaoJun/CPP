#include <atomic>
#include <iostream>
#include <thread>

class Singleton {
private:
    static std::atomic<Singleton*> instance;
    static std::mutex mutex;

    Singleton() {
        // 私有构造函数
    }

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* getInstance() {
        Singleton* tmp = instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            tmp = instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new Singleton();
                std::atomic_thread_fence(std::memory_order_release);
                instance.store(tmp, std::memory_order_relaxed);
            }
        }
        return tmp;
    }

    static void destroyInstance() {
        Singleton* tmp = instance.load(std::memory_order_relaxed);
        if (tmp != nullptr) {
            delete tmp;
            instance.store(nullptr, std::memory_order_relaxed);
        }
    }

    void doSomething() {
        // 执行一些操作
        std::cout << "Singleton is doing something." << std::endl;
    }
};

// 初始化静态成员变量
std::atomic<Singleton*> Singleton::instance(nullptr);
std::mutex Singleton::mutex;

int main() {
    // 创建线程，每个线程获取单例实例并调用 doSomething 函数
    std::thread t1([](){
        Singleton* instance = Singleton::getInstance();
        instance->doSomething();
    });

    std::thread t2([](){
        Singleton* instance = Singleton::getInstance();
        instance->doSomething();
    });

    t1.join();
    t2.join();

    // 销毁单例实例
    Singleton::destroyInstance();

    return 0;
}
