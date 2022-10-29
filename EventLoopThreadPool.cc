#include"EventLoopThreadPool.h"

 EventLoopThreadPool::EventLoopThreadPool(EventLoop*baseLoop,const std::string&name):
    baseLoop_(baseLoop),
    name_(name),
    start_(false),
    numThreads_(0),
    next_(0){

    }
 EventLoopThreadPool::~EventLoopThreadPool(){

 } 

//EventLoopThreadPool创建子线程，并且添加到容器中
void EventLoopThreadPool::start(const ThreadInitCallback&cb){
    for(int i=0;i<numThreads_;i++){
        char buf[name_.size()+32];
        snprintf(buf,name_.size()+31,"%s_%d",name_.c_str(),i);
        EventLoopThread*t=new EventLoopThread(cb,buf);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));
        loops_.push_back(t->startLoop());
    }
    if(numThreads_==0&&cb){
        cb(baseLoop_);
    }
}

//采取轮询的方式获取下一个EventLoop
EventLoop*EventLoopThreadPool::getNextLoop(){
    EventLoop*loop=baseLoop_;

    if(loops_.size()!=0){
        loop=loops_[next_];
        next_=(next_+1)%loops_.size();
    }
    return loop;
}
