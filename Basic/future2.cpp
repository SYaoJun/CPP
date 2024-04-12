#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
int main() {
  auto promise = std::promise<std::string>();

  auto producer = std::thread([&] { promise.set_value("Hello World\n"); });
  // promise包含future，promise是生产者，future是消费者，因为需要通过future.get()获取另一个线程设置的值
  auto future = promise.get_future();

  auto consumer = std::thread([&] { std::cout << future.get(); });

  producer.join();
  consumer.join();
}