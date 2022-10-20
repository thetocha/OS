#ifndef CHANNEL_BUFFERED_CHANNEL_H
#define CHANNEL_BUFFERED_CHANNEL_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size) {
        this->buffer_size = size;
        this->isClose = false;
    }

    void Send(T value) {
        std::unique_lock<std::mutex> q_lock(queue_lock);

        if(isClose){
            throw std::runtime_error("Channel is closed");
        }else{
            while(!isReady){
                queue_is_able.wait(q_lock, [&]{return queue.size() != buffer_size;});
            }
            isReady = false;
            queue.push(value);
            q_lock.unlock();
            isReady = true;
            queue_is_able.notify_one();
        }
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> q_lock(queue_lock);
        while(!isReady){
            queue_is_able.wait(q_lock, [&]{return !(queue.empty());});
        }
        isReady = false;
        T value = queue.front();
        queue.pop();
        q_lock.unlock();
        isReady = true;
        queue_is_able.notify_one();
        return std::make_pair(value,isClose);
    }

    void Close() {
        std::unique_lock<std::mutex> q_lock(queue_lock);
        isClose = true;
        q_lock.unlock();
        queue_is_able.notify_one();
    }

private:
    std::queue<T> queue;
    int buffer_size;
    std::mutex              queue_lock;
    std::condition_variable queue_is_able;
    bool isClose;
    bool isReady;
};

#endif //CHANNEL_BUFFERED_CHANNEL_H
