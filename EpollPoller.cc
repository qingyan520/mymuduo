#include"EpollPoller.h"
#include"Channel.h"
#include"Log.h"
const int kNew=-1;
const int kAdded=1;
const int kDeleted=2;

EpollPoller::EpollPoller(EventLoop*loop):Poller(loop),
  epollfd_(epoll_create1(EPOLL_CLOEXEC)),
  events_(kInitSize){
  if(epollfd_<0)
  {
    LOG(FATAL,"EPOLL_CREATE FAIL!");
    exit(0);
  }
}

EpollPoller::~EpollPoller(){

}

//向epoll中注册感兴趣的事件
void EpollPoller::updateChannel(Channel*channel){
  int index=channel->index();
  if(index==kNew||index==kDeleted){
    int fd=channel->fd();
    if(index==kNew){
      channels_[fd]=channel;
    }
    channel->set_index(kAdded);
    update(EPOLL_CTL_ADD,channel);
  }
  else{  //当前已经注册到epoll中了
    if(channel->isNoneEvent()){
      update(EPOLL_CTL_DEL,channel);
      channel->set_index(kDeleted);
    }
    else{
      update(EPOLL_CTL_MOD,channel);
    }
  }
}

void EpollPoller::removeChannel(Channel*channel){
  int fd=channel->fd();
  if(channel->index()==kAdded){
    update(EPOLL_CTL_DEL,channel);
  }
  channels_.erase(fd);
  channel->set_index(kNew);
}

void EpollPoller::update(int operation,Channel*channel){
  int fd=channel->fd();
  struct epoll_event ent;
  ent.events=channel->events();
  ent.data.ptr=channel;
  int ret=epoll_ctl(epollfd_,operation,fd,&ent);
  if(ret<0){
    if(operation==EPOLL_CTL_DEL){
      LOG(DEBUG,"epoll_ctl::EPOLL_CTL_DEL error!");
    }
    else{
      LOG(FATAL,"epoll_ctl error!");
      exit(0);
    }
  }  
}

Timestamp EpollPoller::poll(int timeOutMs,ChannelList*activeChanneList){
    int numEvents=epoll_wait(epollfd_,&(*events_.begin()),static_cast<int>(events_.size()),timeOutMs);
    Timestamp now(Timestamp::now());
    error_t saveError=errno;
    if(numEvents>0){
      LOG(DEBUG,"epoll_wait success!");
      fillActiveChannelList(numEvents,activeChanneList);
      if(static_cast<int>(events_.size())==numEvents){
                 events_.resize(events_.size()*2);
      }
    }
    else if(numEvents==0){
      LOG(INFO,"epoll_wait nothing happend!");
    }    
    else{
      if(saveError!=ENOTTY){
        LOG(WARING,"epoll_wait error!");
        errno=saveError;
      } 
    }

    return now;
}

void EpollPoller::fillActiveChannelList(int numEvents,ChannelList*activeChanneList){
  for(int i=0;i<numEvents;i++){
    Channel*channel=static_cast<Channel*>(events_[i].data.ptr);
    int revent=events_[i].events;
    channel->set_revens(revent);
    activeChanneList->push_back(channel);
  }
}
