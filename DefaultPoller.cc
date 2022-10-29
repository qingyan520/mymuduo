
#include"Poller.h"
#include"EpollPoller.h"
class EventLoop;
 Poller*Poller::newDefaultPoller(EventLoop*loop){
    if(getenv("DEFAULT_USE_POLL"))
    {
      return  nullptr;
    }
    return new EpollPoller(loop);
}
