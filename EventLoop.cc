#include"EventLoop.h"
#include<sys/eventfd.h>
#include<unistd.h>
#include<fcntl.h>
#include<functional>
#include"Log.h"
#include"Channel.h"
//防止一个线程创建多个EventLoop thread__local
__thread EventLoop*t_loopInThisThread=nullptr;

//定义默认IO复用接口的超时事件
const int kPollTimsMs=1000;

//创建wakeupfd_,用来notify唤醒subReactor处理新来的channel
int createEventfd(){
  int evtfd=eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
  if(evtfd<0){
    LOG(FATAL,"eventfd create errror!");
    exit(0);
  }
  return evtfd;
}

EventLoop::EventLoop():looping_(false),
  quit_(false),
  threadId_(CurrentThread::tid()),
  poller_(Poller::newDefaultPoller(this)),
  wakeupfd_(createEventfd()),
  wakeupChannel_(new Channel(this,wakeupfd_)),
  callPendingFunctors_(false){
    if(t_loopInThisThread!=nullptr){
      LOG(FATAL,"Another EventLoop!");
      exit(0);
    }
    else{
      t_loopInThisThread=this;
    }
    //设置wakeup的事件类型和回调
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead,this));
    //每一个EventLoop都关注wakeupfd_的EPOLLIN事件
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop(){
  wakeupChannel_->disableAll();
  wakeupChannel_->remove();
  close(wakeupfd_);
  t_loopInThisThread=nullptr;
}

void EventLoop::handleRead(){
  uint64_t one=1;
  ssize_t n=read(wakeupfd_,&one,sizeof(one));
  if(n!=sizeof(one)){
    LOG(ERROR,"EventLoop::handleRead error!");
  }
}


void EventLoop::loop(){
  looping_=true;
  quit_=false;

  while(!quit_){
    activeChannels_.clear();

    pollReturnTime_=poller_->poll(kPollTimsMs,&activeChannels_);

    for(Channel*channel:activeChannels_){
      channel->handleEvent(pollReturnTime_);
    }

    doPendingFunctors();
  }
  looping_=false;
}
  

void EventLoop::quit(){
  quit_=true;
  //在其它线程调用quit,比如在一个subloop中调用mainLoop的quit
  if(!isInLoopThread()){
    wakeup();
  }
}

//在当前loop中执行cb
void EventLoop::runInLoop(Functor cb){
  if(isInLoopThread()){
    //在当前loop线程loop中调用runInLoop,执行cb
    cb();
  }
  else{
    //在非当前loop线程中执行cb,那就需要唤醒loop送在线程执行cb
    queueInLoop(cb);
  }
}

void EventLoop::queueInLoop(Functor cb){
  {
    std::unique_lock<std::mutex>lock(mutex_);
    pendingFunctors_.emplace_back(cb);
  }

  //唤醒相应的需要执行上面回调操作的loop线程了
  if(!isInLoopThread()||callPendingFunctors_){
    wakeup();
  }
}


void EventLoop::updateChannel(Channel*channel){
  poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel*channel){
  poller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel*channel){
  return poller_->hasChannel(channel);
}

//用来唤醒loop所在线程的，向wakeupfd_写入一个数据就行
void EventLoop::wakeup(){
  uint64_t one=1;
  ssize_t n=write(wakeupfd_,&one,sizeof(one));
  if(n!=sizeof(one)){
    LOG(WARNING,"write error!");
  }
}

//把cb放入队列中，唤醒loop所在的线程，执行cb
void EventLoop::doPendingFunctors(){
  std::vector<Functor>functors;
  callPendingFunctors_=true;
  {
    std::unique_lock<std::mutex>_lock(mutex_);
    functors.swap(pendingFunctors_);
  }

  for(const Functor&functor:functors){
      functor();
  }

  callPendingFunctors_=false;
}
