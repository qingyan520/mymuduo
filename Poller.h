#pragma once
#include"nocopyable.h"
#include"Timestamp.h"

#include<unordered_map>
#include<vector>
class Channel;
class EventLoop;

class Poller:nocopyable{
  public:
    using ChannelList=std::vector<Channel*>;
    Poller(EventLoop*loop);
    virtual ~Poller();
    
    //子类epollpoller/pollpoller覆写父类虚函数
    virtual Timestamp poll(int timeOutMs,ChannelList*activeChanneList)=0;
    virtual void updateChannel(Channel*channel)=0;
   virtual void removeChannel(Channel*channel)=0;
    
    //返回父类指针
    static Poller*newDefaultPoller(EventLoop*loop);

    //判断channel是否在当前ChannelMap中
    bool hasChannel(Channel*channel)const;

  protected:
    using ChannelMap=std::unordered_map<int,Channel*>;
    ChannelMap channels_;
  private:
    EventLoop*loop_;    
};

