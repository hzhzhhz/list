#include "ThreadPool.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>

ThreadPool::ThreadPool(size_t num):num_(num),is_running(false){

}
ThreadPool::~ThreadPool(){
    if(is_running){
        Stop();
    }
}
void ThreadPool::Start(){
    is_running=true;
    /*初始化时启动所有线程，等待任务*/
    for(size_t i=0;i<num_;i++){
        threads_.emplace_back(new std::thread(&ThreadPool::Work,this));
    }
}
void ThreadPool::Stop(){
    std::unique_lock<std::mutex> lock(mutex_);
    /*注销线程前停止循环状态*/
    is_running=false;
    lock.unlock();
    condition_.notify_all();
    std::for_each(threads_.begin(),threads_.end(),[](std::thread* thread_){
        if(thread_->joinable()){
            thread_->join();
            delete thread_;
            thread_=nullptr;
        }
    });
    
}

void ThreadPool::Work(){
    while(is_running){
        Task task;
        std::cout<<"current thread id :"<<std::this_thread::get_id()<<std::endl;
        std::unique_lock<std::mutex> lock(mutex_);
        if(!tasks_.empty()){
            task=std::move(tasks_.front());
            tasks_.pop();
        }
        /*需要判断是否还在运行*/
        else if(is_running&&tasks_.empty()){
            condition_.wait(lock);
        }
        if(task){
            /*执行任务*/
            task();
        }
    }
}

void ThreadPool::AppendThread(const Task &task){
    if(is_running){
        std::lock_guard<std::mutex>lock (mutex_);
        tasks_.push(task);
        condition_.notify_all();
    }
}
