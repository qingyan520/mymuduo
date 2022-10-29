//TcpConnection
#pragma once
#include"nocopyable.h"
#include"Callbacks.h"
#include"Timestamp.h"
#include"InetAddress.h"
#include"Buffer.h"
#include<memory.h>
#include<functional>
#include<atomic>
#include<string>
class Channel;
class EventLoop;
class Socket;


//TcpServer==>Acceptor==>有一个新用户连接，通过acceptor函数拿到connfd
//TcpConnection设置回调==>Channnel==>Poller==>调用Channel的回调操作
class TcpConnection:nocopyable,public std::enable_shared_from_this<TcpConnection>{
    public:
    TcpConnection(EventLoop*loop,const std::string&name,int sockfd,const InetAddress&localAddr,const InetAddress&peerAddr);
    ~TcpConnection();

    EventLoop*getLoop()const{return loop_;}
    const std::string&name()const{return name_;}
    const InetAddress&loaclAddress() const{return this->localAddr_;}
    const InetAddress&peerAddress() const{return this->peerAddr_;}

    bool connected()const{return state_==kConnected;}
    bool disconnected()const{return state_==kDisconnected;}

    //发送数据
    void send(const string&buf);
    void sendInLoop(const char*message,size_t len);
    //关闭连接
    void shutdown();

    //设置回调
    void setConnectionCallback(const ConnectionCallback&cb){connectionCallback_=std::move(cb);}
    void setMessageCallback(const MessageCallback&cb){messageCallback_=std::move(cb);}
    void setWriteCompleteCallback(const WriteCompleteCallback&cb){writeCompleteCallback_=std::move(cb);}
    void setHighWaterMarkCallback(const HighWaterMarkCallback&cb){highWatermarkCallback_=std::move(cb);}
    void setCloseCallback(const CloseCallback&cb){closeCallback_=std::move(cb);}

    //连接建立
    void connectEstablished();
    //连接销毁
    void connectDestroyed();


    private:

    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

  //  void sendInLoop(const void*message,const size_t len);
    void shutdownInLoop();

    enum StateE{kDisconnected,kConnecting,kConnected,kDisconnecting};//已经断开连接，正在连接，连接了，正在断开连接
    void setState(StateE state){state_=state;}


    EventLoop*loop_;  //这里的loop_是subloop,此时mainloop接受客户端连接，将这个连接分配给subloop,打包成tcpConnection
    
    const std::string name_;   //记录服务器名称
    std::atomic_int  state_;   //记录连接专题状态
    bool reading_;

    std::unique_ptr<Socket>socket_;
    std::unique_ptr<Channel>channel_;

    const InetAddress localAddr_;
    const InetAddress peerAddr_;


    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    HighWaterMarkCallback highWatermarkCallback_;
    CloseCallback closeCallback_;

    size_t highWaterMark_;
    Buffer inputBuffer_;
    Buffer outputBuffer_;
};
