#include"Thread.h"
#include"CurrentThread.h"
#include<semaphore.h>

Thread::Thread(ThreadFunc func, const std::string &name):
  started_(false),
  joined_(false),
  tid_(0),
  func_(std::move(func)),
  name_(name){
    setDefaultName();
}

Thread::~Thread(){
  if(started_&&!joined_){
    thread_->detach();      //thread类提供了设置分离线程的方法
  }
}

void Thread::setDefaultName(){
  int num=++numCreated_;
  if(name_.empty()){
    name_="thread "+std::to_string(num);
  }
}

void Thread::start(){
    //一个Thread记录的就是一个新线程的详细信息
    started_=true;

    //semaphore信号量保证在start末尾出可以得到线程id
    sem_t sem;
    sem_init(&sem,false,0);
    thread_=std::shared_ptr<std::thread>(new std::thread([&](){
            tid_=CurrentThread::tid();           //得到线程id
            sem_post(&sem);                      //信号量进行post
            func_();                             //执行线程函数
          }));

    //在这里必须保证得到了线程id
    sem_wait(&sem);
}

void Thread::join(){
  joined_=true;
  thread_->join();
}
