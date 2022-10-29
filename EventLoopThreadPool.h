#pragma once
#include"EventLoopThread.h"
#include<vector>
#include<string>
class EventLoopThreadPool{
    public:
    using ThreadInitCallback=std::function<void(EventLoop*)>;

    EventLoopThreadPool(EventLoop*baseLoop,const std::string&name=std::string());
    ~EventLoopThreadPool();

    void start(const ThreadInitCallback&cb=ThreadInitCallback());
    EventLoop*getNextLoop();

    bool started()const {return start_;}
    void setThreadNum(int num){numThreads_=num;}

    private:
    EventLoop*baseLoop_;                  //baseLoop_，用户传进来的主loop
    std::string name_;                         //线程池名称
    bool start_;                          //
    int numThreads_;                      //线程数量
    int next_;                            //轮询的方式拿到EventLoop
    std::vector<std::unique_ptr<EventLoopThread>>threads_;      //存放EventLoopThread指针
    std::vector<EventLoop*>loops_;       //存放所有的Eventloop
};