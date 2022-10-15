#include"Channel.h"
#include"EventLoop.h"
#include<sys/epoll.h>

const int Channel::kNoneEvent=0;
const int Channel::kReadEvent=EPOLLIN|EPOLLPRI;
const int Channel::kWriteEvent=EPOLLOUT;

Channel::Channel(EventLoop*loop,int fd):
  loop_(loop),
  fd_(fd),
  events_(0),
  revents_(0),
  index_(-1),
  tied_(false){

  }

Channel::~Channel(){

}

void Channel::handleEvent(Timestamp receviTime){
  if(tied_)
  {
    std::shared_ptr<void>guard=tie_.lock();
    if(guard)
    {
      handleEventWithGuard(receviTime);
    }
  }
  else
  {
    handleEventWithGuard(receviTime);
  }
}

void Channel::handleEventWithGuard(Timestamp receviTime){
  if(revents_&EPOLLHUP&&!(revents_&EPOLLIN))
  {
    if(closeCallback_)
    {
      closeCallback_();
    }
  }
  if(revents_&EPOLLERR)
  {
    if(errorCallback_)
    {
      errorCallback_();
    }
  }
  if(revents_&(EPOLLIN|EPOLLPRI))
  {
    if(readCallback_)
    {
      readCallback_(receviTime);
    } 
  }
  if(revents_&EPOLLOUT)
  {
    if(writeCallback_)
    {
      writeCallback_();
    }
  }
}

void Channel::remove()
{
  //add code..
  //loop_->removeChannel(this);
}

void Channel::update(){
  //loop->_updateChannel(this);
}
