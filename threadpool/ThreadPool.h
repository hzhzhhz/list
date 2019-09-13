#ifndef _threadpool_
#define _threadpool_
#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>

class ThreadPool{
public:
    /*利用function实现函数模板*/
    using Task=std::function<void()>;

    ThreadPool(size_t num);
    ~ThreadPool();
    void Start();
    void Stop();
    void AppendThread(const Task &);
private:
    ThreadPool(const ThreadPool&)=default;
    ThreadPool& operator =(const ThreadPool&)=default;
    void Work();
private:
    size_t num_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<Task>tasks_;
    std::vector<std::thread*>threads_;
    bool is_running;
};
#endif
