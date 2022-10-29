#include"TcpServer.h"
EventLoop*check_loop(EventLoop*loop){
    if(loop==nullptr){
        LOG(FALTA,"TcpServer::EventLoop is nullptr!");
        exit(0);
    }
    return loop;
}

TcpServer::TcpServer(EventLoop*loop,const InetAddress&listenAddr,const std::string &name,option opt)
    :loop_(check_loop(loop)),
    name_(name),
    ipPort_(listenAddr.toIpPort()),
    acceptor_(new Acceptor(loop,listenAddr,opt==TcpServer::kReusePort)),
    threadPool_(new EventLoopThreadPool(loop,name_)),
    connectionCallback_(),
    messageCallback_(),
    started_(0),
    nexConnId_(1){
        //新用户连接时，执行newConnecitonCallback
        acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection,this,std::placeholders::_1,std::placeholders::_2));
    }

//当mainLoop的acceptor_ acceptor到一个新用户连接connfd，
//会执行NewConnection回调，这个回调会采取轮询算法将这个connfd打包成TcpConnection，
//然后将这个fd分配给subloop

void TcpServer::setThreadNum(int numThreas){
    threadPool_->setThreadNum(numThreas);
}

void TcpServer::start()
{
    //防止一个TcpServer被启动多次
    if(++started_==1)
    {
        threadPool_->start();
        loop_->runInLoop(std::bind(&Acceptor::listen,acceptor_.get()));
    }
}


//有一个新用户连接，Acceptor的handleRead函数会执行TcpServer::newConnection回调函数
void TcpServer::newConnection(int sockfd,const InetAddress&peerAddr)
{
    //轮询算法选择以一个subLoop来管理channel_;
    EventLoop*ioLoop=threadPool_->getNextLoop();
    char buf[64]{0};
    snprintf(buf,sizeof(buf),"-%s,#%d",peerAddr.toIpPort().c_str(),this->nexConnId_);
    ++nexConnId_;
    string connName=name_+buf;

    LOG(INFO,"TcpCServer::newConnection "+name_+"new Connection from "+peerAddr.toIpPort());

    //通过sockfd回去其绑定的本机ip地址和端口信息
    sockaddr_in local;
    socklen_t addrlen=sizeof(local);
    if(::getsockname(sockfd,(sockaddr*)&local,&addrlen)<0)
    {
        LOG(WARNING,"sockets::getLocalAddr");
    }

    //通过sockfd获取本地ip+port
    InetAddress localAddr(local);

    //创建TcpConnection连接对象
    TcpConnectionPtr conPtr(new TcpConnection(ioLoop,connName,sockfd,localAddr,peerAddr));
    connections_[connName]=conPtr;

    //给TcpConnection设置回调
    conPtr->setConnectionCallback(connectionCallback_);
    conPtr->setMessageCallback(messageCallback_);
    conPtr->setWriteCompleteCallback(writeComplateCallback_);

    //设置如何关闭连接的回调
    conPtr->setCloseCallback(std::bind(&TcpServer::removeConnection,this,std::placeholders::_1));    
    
    //调用TcpConnection::connectEstablish
    ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished,conPtr));

}


void TcpServer::removeConnection(const TcpConnectionPtr&conn){
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionOnLoop,this,conn));
}

void TcpServer::removeConnectionOnLoop(const TcpConnectionPtr&conn){


    size_t n=connections_.erase(conn->name());
    EventLoop*ioLoop=conn->getLoop();
    ioLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed,conn));
}

TcpServer::~TcpServer()
{
    for(auto &item:connections_)
    {
        //这个局部的conn出右括号自动销毁
        TcpConnectionPtr conn(item.second);
        item.second.reset();
        //销毁连接
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed,conn));
    }
}