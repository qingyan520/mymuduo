#pragma once

#include"nocopyable.h"
#include<functional>
#include<thread>
#include<memory>
#include<string>
#include<atomic>
using std::string;
class Thread:nocopyable{
  public:
    using ThreadFunc=std::function<void()>;
    explicit Thread(ThreadFunc func,const string&name=string());
    ~Thread();
    void start();
    void join();
    bool started()const{return  started_;}
    pid_t tid() {return tid_;}
    std::string name()const { return name_;}
    static int numCreated(){return numCreated_;}
  private:
    void setDefaultName();
    bool started_;
    bool joined_;
    std::shared_ptr<std::thread>thread_;
    pid_t tid_;
    ThreadFunc func_;
    string name_;
    static std::atomic_int numCreated_;
};
