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
// Hash 3929
// Hash 7649
// Hash 8567
// Hash 8024
// Hash 1824
// Hash 8489
// Hash 7717
// Hash 5095
// Hash 3598
// Hash 5542
// Hash 3964
// Hash 4535
// Hash 7935
// Hash 9039
// Hash 7403
// Hash 3303
// Hash 5934
// Hash 8430
// Hash 2823
// Hash 3149
// Hash 4106
// Hash 5072
// Hash 2507
// Hash 7168
// Hash 5724
// Hash 6482
// Hash 4187
// Hash 9068
// Hash 5397
// Hash 5976
// Hash 4178
// Hash 9491
// Hash 1053
// Hash 5195
// Hash 8844
// Hash 6829
// Hash 6386
// Hash 5950
// Hash 4569
// Hash 6604
// Hash 3454
// Hash 8604
// Hash 2335
// Hash 6866
// Hash 1321
// Hash 1646
// Hash 7380
// Hash 9653
// Hash 9029
// Hash 8742
// Hash 1670
// Hash 8727
// Hash 4149
// Hash 5115
// Hash 7015
// Hash 5318
// Hash 7478
// Hash 6054
// Hash 5024
// Hash 7076
// Hash 2677
// Hash 8365
// Hash 1448
// Hash 2272
// Hash 3734
// Hash 4659
// Hash 9987
// Hash 2810
// Hash 4192
// Hash 6774
// Hash 1558
// Hash 7122
// Hash 8380
// Hash 5053
// Hash 1493
// Hash 2881
// Hash 6646
// Hash 3886
// Hash 7599
// Hash 7143
// Hash 8608
// Hash 7352