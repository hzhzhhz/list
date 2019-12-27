#include "message.h"
#include <unistd.h>
#include <iostream>
using namespace std;

struct TASK{
    int type;
    std::string rtsp;
    std::string ip;
};
using task_ptr=shared_ptr<TASK>;
MessageQueue<task_ptr>MESS;

void _get(){
    while(1){
        task_ptr one_task;
        MESS.Pop(one_task,true);
        cout<<"type"<<one_task->type<<endl;
        cout<<"rtsp"<<one_task->rtsp<<endl;
        cout<<"ip"<<one_task->ip<<endl;
        sleep(4);
    }
}
int main(){

    task_ptr _task;
    TASK task{3,"a","asd"};
    std::thread t(_get);
    while(1){

         _task=make_shared<TASK>(task);
        MESS.Push(_task);
        sleep(3);
    }
