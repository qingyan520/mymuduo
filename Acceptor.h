#pragma once
#include"Socket.h"
#include"InetAddress.h"
#include"Channel.h"
#include<functional>
class EventLoop;

class Acceptor{
    public:
    using NewConnectionCallback=std::function<void(int fd,const InetAddress&addr)>;
    Acceptor(EventLoop*loop,const InetAddress&addr,bool reuse=true);

    ~Acceptor();

    void listen();
    bool listening()const{return listenning_;}
    void setNewConnectionCallback(const NewConnectionCallback&cb){newConnectionCallback_=std::move(cb);}

    private:
    void handleRead();
    EventLoop*loop_;
    Socket acceptSocket_;
    Channel accpetChannel_;
    bool listenning_;
    NewConnectionCallback newConnectionCallback_;

};