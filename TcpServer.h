#pragma once
#include"Callbacks.h"
#include"InetAddress.h"
#include"Acceptor.h"
#include"nocopyable.h"
#include"EventLoopThreadPool.h"
#include"EventLoop.h"
#include"Log.h"
#include"TcpConnection.h"
#include<functional>
#include<string>
#include<unordered_map>

class TcpServer:nocopyable{
    public:
    using ThreadInitCallback=std::function<void(EventLoop*)>;
    using ConnectionMap=std::unordered_map<std::string,TcpConnectionPtr>;
    
    enum option{
        kNoReusePort,
        kReusePort
    };

    TcpServer(EventLoop*loop,const InetAddress&listenAddr,const string&name=string(),option opt=kReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback&cb){threadInitCallback_=std::move(cb);}
    void setConnectionCallback(const ConnectionCallback&cb){connectionCallback_=std::move(cb);}
    void setMessageCallback(const MessageCallback&cb){messageCallback_=std::move(cb);}
    void setWriteCompleteCallback(const WriteCompleteCallback&cb){writeComplateCallback_=std::move(cb);}

    //设置线程池线程数量
    void setThreadNum(int numThreads);
    //开始服务器
    void start();


    private:

    void newConnection(int sockfd,const InetAddress&peerAddr);
    void removeConnection(const TcpConnectionPtr&conn);
    void removeConnectionOnLoop(const TcpConnectionPtr&conn);


    EventLoop*loop_;
    
    const std::string name_;
    const std::string ipPort_;

    std::unique_ptr<Acceptor>acceptor_;  //运行再mainloop中，监听新用户连接
    std::shared_ptr<EventLoopThreadPool>threadPool_;//one loop per thread

    ConnectionCallback connectionCallback_;  //有新用户到来时的回调
    MessageCallback messageCallback_;   //接受消息执行的回调
    WriteCompleteCallback writeComplateCallback_; //消息发送以后的回调
    ThreadInitCallback threadInitCallback_;   //loop线程初始化时候的回调
    
    std::atomic_int started_;
    int nexConnId_;

    ConnectionMap connections_;  //保存所有的连接
};
