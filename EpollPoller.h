#include"Poller.h"
#include<sys/epoll.h>
class EpollPoller:public Poller{
  public:
    EpollPoller(EventLoop*loop);
    ~EpollPoller()override;
    Timestamp poll(int timeOutMs,ChannelList*atciveChannel)override;
    void updateChannel(Channel*channel)override;
    void removeChannel(Channel*channel)override;
    
  private:
    const int kInitSize=16;
    void update(int operation,Channel*channel);
    void fillActiveChannelList(int numEvents,ChannelList*activeChanneList);
    int epollfd_;
    std::vector<struct epoll_event>events_;
};


