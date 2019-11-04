#ifndef _logger_
#define _logger_

#include <iostream>
#include <string>
#include <vector>
#include <sys/time.h>

class Logger{
public:
    enum{TRACE,DEBUG,INFO,WARNING,ERROR};
    Logger(){};
    //static void Log(const int level,const std::string &file,const int line,const char* format,...);
    /*log函数
    level:  打印日志等级
    format: 日志描述
    ...:    追加变量*/
    static void Log(const int level,const char* format,...);
    //static void Log(const int level,const char* format);
    /*设置当前日志等级*/
    static void SetCurrentLevel(int level);
    /*获取当前时间，精确到秒*/
    static std::string GetCurrentTime();
private:
    static std::ostream& output_; 
    static int current_level_;
    static std::vector<std::string>level_to_string_;
};
#endif