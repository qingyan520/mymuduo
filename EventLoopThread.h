#include"nocopyable.h"
#include"Thread.h"
#include<functional>
#include<string>
#include<mutex>
#include<condition_variable>
class EventLoop;

class EventLoopThread{
  public:
    using ThreadInitCallback=std::function<void(EventLoop*)>;
    EventLoopThread(const ThreadInitCallback &cb=ThreadInitCallback(),const string &name=string());
    ~EventLoopThread();
    EventLoop*startLoop();
  private:
    void threadfunc();                     //thread绑定的函数，在这个函数里获取EventLoop
    EventLoop*loop_;                       //loop与thread线程一一对应，即one loop per thread
    bool exiting_;                         //退出时进行设定
    Thread thread_;                        //Thread线程类，绑定threadfunc函数，
    std::mutex mtx_;                       //互斥锁
    std::condition_variable cond_;         //条件变量
    ThreadInitCallback threadInitCallback_;//线程初始化执行的函数
};

