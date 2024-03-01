#include <iostream>
#include <atomic>
#include <thread>
#include <memory>
struct Node {
    int data;
    std::shared_ptr<Node> next;
    unsigned int version;  // Additional version number

    Node(int val, unsigned int ver) : data(val), next(nullptr), version(ver) {}
};

int main() {
    // Initialize a shared_ptr with a Node
    std::shared_ptr<Node> head = std::make_shared<Node>(1, 1);

    // Create an atomic shared_ptr with the initial value
    std::atomic<std::shared_ptr<Node>> atomicHead(head);

    // Simulate ABA scenario
    std::thread t1([&]() {
        std::shared_ptr<Node> newHead = std::make_shared<Node>(2, head->version + 1);
        atomicHead.store(newHead);
    });

    std::thread t2([&]() {
        // Sleep to let t1 execute first
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // ABA problem: Reset the head to its original value
        std::shared_ptr<Node> newHead = std::make_shared<Node>(1, head->version + 1);
        atomicHead.store(newHead);
    });

    t1.join();
    t2.join();

    // Check for ABA using compare_exchange_weak
    std::shared_ptr<Node> expected = head;
    std::shared_ptr<Node> updated = std::make_shared<Node>(3, expected->version + 1);

    bool success = atomicHead.compare_exchange_weak(expected, updated);

    if (success) {
        std::cout << "CAS successful. Updated head: " << atomicHead.load().get()->data << std::endl;
    } else {
        std::cout << "CAS failed. Current head: " << atomicHead.load().get()->data << std::endl;
    }

    return 0;
}
