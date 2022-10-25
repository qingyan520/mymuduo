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
    using ThreadFunc=std::function<void()>;      //回调函数
    explicit Thread(ThreadFunc func,const string&name=string());
    ~Thread();
    void start();        //启动线程
    void join();
    bool started()const{return  started_;}      
    pid_t tid() {return tid_;}    //得到线程的pid值
    std::string name()const { return name_;}   //返回线程名称
    static int numCreated(){return numCreated_;}   //返回线程数量
  private:
    void setDefaultName();    //设置默认的线程名称
    bool started_;            //线程启动
    bool joined_;             //标记线程是joined的
    std::shared_ptr<std::thread>thread_;     //智能指针灵活管理，使得在指定地方启动线程
    pid_t tid_;               //得到线程pid值
    ThreadFunc func_;         //线程要执行的函数
    string name_;             //线程名称
    static std::atomic_int numCreated_;  //线程数量
};
