#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<future>  //std::future std::promise

void fun(int x, int y, std::promise<int>& promiseObj) {
	promiseObj.set_value(x + y);
    std::cout<<"sleep 1 second"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // promiseObj.set_value(x + y + 10); 不能设置两次
}

int main()
{
	int a = 10;
	int b = 8;

	// 声明一个promise类
	std::promise<int> promiseObj;
	// 将future和promise关联
	std::future<int> futureObj = promiseObj.get_future();
	// 模板传参的时候使用ref，否则传参失败
	std::thread t(fun, a, b, std::ref(promiseObj));
	t.join();
    
	// 获取线程的"返回值"
	int sum = futureObj.get();
	std::cout << "sum=" << sum << std::endl; // 输出：18
    sum = futureObj.get();
    std::cout << "sum=" << sum << std::endl; // 输出：18
	return 0;
}
