#ifndef _message
#define _message

#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

template <class Type>
class MessageQueue{
    MessageQueue &operator = (const MessageQueue &)=delete;
    MessageQueue (const MessageQueue &m)=delete;
public:
    MessageQueue():_queue(),_mutex(),_condition(){}
    ~MessageQueue(){}
    void Push(Type record){
        std::lock_guard<std::mutex>lock(_mutex);
        _queue.push(record);
        _condition.notify_one();
    }
    bool Pop(Type & record,bool isBlocked =true){
        if(isBlocked){
            std::unique_lock<std::mutex>lock(_mutex);
            while(_queue.empty()){
                _condition.wait(lock);
            }
        }
        else{
            std::lock_guard<std::mutex>lock(_mutex);
            if(_queue.empty()){
                return false;
            }
        }
        record = std::move(_queue.front());
        _queue.pop();
        return true;
    }
    size_t Size(){
        std::lock_guard<std::mutex>lock(_mutex);
        return _queue.size();
    }
    bool Empty(){
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }
private:
    mutable std::mutex _mutex;
    std::condition_variable _condition;
    std::queue<Type>_queue;
};
#endif
