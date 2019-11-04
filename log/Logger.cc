#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>

using std::string;
using std::vector;

std::ostream& Logger::output_(std::cout);
vector<string> Logger::level_to_string_{"TRACE","DEBUG","INFO","WARNING","ERROR"};
int Logger::current_level_=ERROR;


string Logger::GetCurrentTime(){
    struct timeval current_time;
    char time_buff[64];
    gettimeofday(&current_time,NULL);
    strftime(time_buff,sizeof(time_buff)-1,"%Y-%m-%d %H:%M:%S",localtime(&current_time.tv_sec));
    return time_buff;
}
// void Logger::Log(const int level,const string &file,const int line,const char* format,...){
//     if(level<=current_level_){
//         string level_str=level_to_string_[level];
//         string context=GetCurrentTime();
//         context.push_back(' ');

//         context.append(file);
//         context.push_back(' ');

//         context.append(std::to_string(line));
//         context.push_back(' ');

//         context.push_back('[');
//         context.append(level_str);
//         context.push_back(']');

//         context.push_back(' ');
//         context.append("Face");
//         context.push_back(':');
//         context.push_back(' ');

//         va_list va_;
//         va_start(va_,format);
//         context.append(va_arg(va_,const char*));
//         va_end(va_);
//         output_<<context<<std::endl;
//     }
// }


void Logger::Log(const int level,const char* format,...){
    if(level<=current_level_){
        char buf[100];
        string level_str=level_to_string_[level];
        string context=GetCurrentTime();
        context.push_back(' ');
        context.push_back('[');
        context.append(level_str);
        context.push_back(']');
        context.push_back(' ');

        va_list va_;
        va_start(va_,format);
        sprintf(buf,format,va_arg(va_,char*));
        context.append(buf);
        va_end(va_);
        output_<<context<<std::endl;
    }
}

// void Logger::Log(const int level,const char* format){
//     if(level<=current_level_){
//         string level_str=level_to_string_[level];
//         string context=GetCurrentTime();
//         context.push_back(' ');

//         context.append(level_str);
//         context.push_back(' ');

//         context.append(format);
//         output_<<context<<std::endl;
//     }
// }
void Logger::SetCurrentLevel(const int level){
    current_level_=level;
}