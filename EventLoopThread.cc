#include"EventLoopThread.h"
#include"EventLoop.h"
EventLoopThread::EventLoopThread(const ThreadInitCallback&cb,const string&name):
  loop_(nullptr),
  exiting_(false),
  thread_(std::bind(&EventLoopThread::threadfunc,this),name),
  mtx_(),
  cond_(),
  threadInitCallback_(std::move(cb)){

  }

EventLoopThread::~EventLoopThread(){
  exiting_=true;
  thread_.join();
}

EventLoop*EventLoopThread::startLoop(){
  thread_.start();

  EventLoop*loop=nullptr;
  {
    std::unique_lock<std::mutex>lock(this->mtx_);
    while(loop_==nullptr)
    {
      cond_.wait(lock);
    }
    loop=loop_;
  }
  return loop;

}

void EventLoopThread::threadfunc(){
  EventLoop loop;

  if(threadInitCallback_)
  {
    threadInitCallback_(&loop);
  }

  {
    std::unique_lock<std::mutex>lock(this->mtx_);
    loop_=&loop;
    cond_.notify_one();
  }
  //开启事件循环
  loop.loop();

   std::unique_lock<std::mutex>lock(this->mtx_);
   loop_=nullptr;
}