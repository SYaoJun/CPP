#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable cv;
std::mutex cv_m; // This mutex is used for three purposes:
// 1) to synchronize accesses to i
// 2) to synchronize accesses to std::cerr
// 3) for the condition variable cv
int i = 0;

void waits()
{
    std::unique_lock<std::mutex> lk(cv_m);
    std::cerr << "Waiting... \n";
    cv.wait_for(lk, std::chrono::seconds(10), []{return i == 1;});
    if(i == 1){
        std::cout<<"awake by condition, i = "<<i<<std::endl;
    }else{
        std::cout<<"awake for timeout"<<std::endl;
    }
    i++; // 第一个获取到锁的人将条件i变成了2，这样其他人就获取不到锁了
}
/*
Waiting... 
Waiting... 
Waiting... 
Notifying...
Notifying again...
awake by condition, i = 1
awake for timeout
awake for timeout
*/

void signals()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lk(cv_m); // 通过这里可以证明在条件变量阻塞期间是将锁释放掉的
        std::cerr << "Notifying...\n";
    }
    cv.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
        std::cerr << "Notifying again...\n";
    }
    cv.notify_all();
}

int main()
{
    std::thread t1(waits), t2(waits), t3(waits), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}