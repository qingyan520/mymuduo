#include"Acceptor.h"
#include"Log.h"
#include<sys/socket.h>
#include<unistd.h>
static int CreateNoBlocking()
{
    int fd=socket(AF_INET,SOCK_STREAM|SOCK_CLOEXEC|SOCK_NONBLOCK,0);
    if(fd<0)
    {
        LOG(FALTA,"create sockfd error!");
        exit(0);
    }
    return fd;
}

Acceptor::Acceptor(EventLoop*loop,const InetAddress&addr,bool reuse):
    loop_(loop),
    acceptSocket_(CreateNoBlocking()),
    accpetChannel_(loop_,acceptSocket_.fd()),
    listenning_(false)
{
    acceptSocket_.setKeepAlive(reuse);
    acceptSocket_.setReuseAddr(reuse);
    acceptSocket_.setReusePort(reuse);
    acceptSocket_.setTcpNoDelay(reuse);
    acceptSocket_.bindAddress(addr);
    accpetChannel_.setReadCallback(std::bind(&Acceptor::handleRead,this));
}
    
Acceptor::~Acceptor()
{
    accpetChannel_.disableAll();
    accpetChannel_.remove();
}

void Acceptor::listen()
{
    listenning_=true;
    acceptSocket_.listen();
    accpetChannel_.enableReading();
}

void Acceptor::handleRead()
{
    InetAddress addr;
    int confd=acceptSocket_.accept(&addr);

    if(confd>=0)
    {
        if(newConnectionCallback_)
        {
            newConnectionCallback_(confd,addr);
        }
        else
        {
            ::close(confd);
        }
    }
    else
    {
        LOG(WARNING,"accept error ,confd<0!");
        if(errno==EMFILE)
        {
            LOG(WARNING,"sockfd get limited!");
        }
    }
}