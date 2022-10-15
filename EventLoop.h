#pragma once 
#include"nocopyable.h"
#include"CurrentThread.h"
#include"Timestamp.h"
#include"EpollPoller.h"
#include<memory>
#include<vector>
#include<atomic>
#include<mutex>
#include<functional>
class Channel;
class EventLoop:nocopyable{
  public:
    using Functor=std::function<void()>;
    EventLoop();
    ~EventLoop();

    //开启事件循环
    void loop();
    //退出事件循环
    void quit();

    Timestamp pollReturnTime()const{return pollReturnTime_;}

    //在当前loop中执行cb
    void runInLoop(Functor cb);
    //把cb放入队列中，唤醒loop所在线程，执行cb
    void queueInLoop(Functor cb);
    //唤醒loop所在的线程
    void wakeup();


    //EventLoop的方法调用poller的方法
    void updateChannel(Channel*channel);
    void removeChannel(Channel*channel);
    bool hasChannel(Channel*channel);

    //判断EventLoop是否在当前线程中
    bool isInLoopThread()const{return threadId_==CurrentThread::tid();}

  private:
    void handleRead();    //wake up
    void doPendingFunctors();   //执行回调

    using ChannelList=std::vector<Channel*>;

    std::atomic_bool looping_;
    std::atomic_bool quit_;     //标志退出loop循环

    const pid_t threadId_;   //记录loop所在线程id
    Timestamp pollReturnTime_ ; //poller返回事件channnels的时间点
    std::unique_ptr<Poller>poller_;
      
    int wakeupfd_;
    std::unique_ptr<Channel>wakeupChannel_;

    ChannelList activeChannels_;
    std::vector<Functor>pendingFunctors_; //存储
    std::atomic_bool callPendingFunctors_;
    std::mutex mutex_;  //互斥锁保护vector容器的线程安全操作
};
