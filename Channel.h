#pragma once 
#include"nocopyable.h"
#include"Timestamp.h"

#include<memory>
#include<functional>

class EventLoop;

class Channel{
  public:
    using ReadEventCallback=std::function<void(Timestamp)>;
    using EventCallback=std::function<void()>;

    Channel(EventLoop*loop,int fd);
    ~Channel();

    void handleEvent(Timestamp receviTime);
    
    //设置对应的回调函数
    void setReadCallback(ReadEventCallback cb){readCallback_=std::move(cb);}
    void setWriteCallback(EventCallback cb){writeCallback_=std::move(cb);}
    void setErrorCallback(EventCallback cb){errorCallback_=std::move(cb);}
    void setCloseCallback(EventCallback cb){closeCallback_=std::move(cb);}

    //设置fd感兴趣的事件，注册到epoll上
    void enableReading(){events_|=kReadEvent;update();}
    void disableReading(){events_&=~kReadEvent;update();}
    void enableWriting(){events_|=kWriteEvent;update();}
    void disableWriting(){events_&=~kWriteEvent;update();}
    void disableAll(){events_=kNoneEvent;update();}

    //判断fd对那个事件感兴趣
    bool isReading()const{return revents_&kReadEvent;}
    bool isWriting()const{return revents_&kWriteEvent;}
    bool isNoneEvent()const{return revents_==kNoneEvent;}
    
    //返回基础信息
    int fd()const{return fd_;}
    int events()const{return events_;}
    void set_revens(int revt){revents_=revt;}
    int index(){return index_;}
    void set_index(int idx){index_=idx;}
    EventLoop*owerLoop(){return loop_;}
    void tie(const std::shared_ptr<void>&sp){tied_=true;tie_=sp;}
    
    void remove();     //删除channel
  private:
    
    void update();
    void handleEventWithGuard(Timestamp receviTime);

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop*loop_;
    int fd_;
    int events_;
    int revents_;
    int index_;

    bool tied_;
    std::weak_ptr<void>tie_;

    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;
    EventCallback closeCallback_;
};
