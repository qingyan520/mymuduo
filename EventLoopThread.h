#pragma once 
#include"nocopyable.h"
#include"Thread.h"
#include"EventLoop.h"
#include<mutex>
#include<condition_variable>
class EventLoopThread:nocopyable{
  public:
    using ThreadInitCallback=std::function<void(EventLoop*)>;
    EventLoopThread(const ThreadInitCallback&cb=ThreadInitCallback(),const std::string&name=string());
    ~EventLoopThread();
    EventLoop*startLoop();
  private:
    void threadFunc();
    EventLoop*loop_;
    bool exiting_;
    Thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;
    ThreadInitCallback callback_;
};
