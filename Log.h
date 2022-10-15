#pragma once 
#include<time.h>
#include<string>
//日志打印      
   #define INFO 1 
   #define WARNING 2
   #define DEBUG 3                                            
   #define FALTA 4                                                                           
                    
   #define LOG(level,message)  log(#level,message,__FILE__,__LINE__)
   static void log(std::string level, std::string message, std::string file_name, int line) {
     //if(level=="DEBUG")
     //  return;
      //显示当前事件   
      char now[1024] = { 0 };
      time_t tt = time(nullptr);                      
      struct tm* ttime;                                                                                                                     
      ttime = localtime(&tt);
      strftime(now, 1024, "%Y-%m-%d %H:%M:%S", ttime);                                               
      // cout << "[" << now << "" << "][" << level << "]" << "[" << message << "]" << "[" << file_name << "]" << "[" << line << "]" << endl;
                                                                                                                                                                                                 
      printf("[%s][%s][%s][%s][%d]\n", now, level.c_str(), message.c_str(), file_name.c_str(), line);
                                           
   } 
