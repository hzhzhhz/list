#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

void test1(){
    std::cout<<"a"<<std::endl;
}
int test2(){
    std::cout<<"b"<<std::endl;
}
int main(){
    ThreadPool thread_pool_(10);
    thread_pool_.Start();
    for(int i=0;i<10;i++){
        thread_pool_.AppendThread(std::bind(test1));
        sleep(1);
        thread_pool_.AppendThread(std::bind(test2));
    }
    thread_pool_.Stop();
    return 0;
}
