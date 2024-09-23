#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Hash 1088
// Hash 9383
// Hash 7388
// Hash 5745
// Hash 8035
// Hash 7451
// Hash 7926
// Hash 2202
// Hash 7030
// Hash 5089
// Hash 9398
// Hash 8422
// Hash 1342
// Hash 3357
// Hash 9655
// Hash 1504
// Hash 6363
// Hash 2926
// Hash 3364
// Hash 8444
// Hash 6240
// Hash 9831
// Hash 3661
// Hash 8121
// Hash 5418
// Hash 9910
// Hash 6148
// Hash 6118
// Hash 2247
// Hash 7865
// Hash 9006
// Hash 2400
// Hash 7030