#include"Socket.h"
#include"Log.h"
#include<unistd.h>
#include <netinet/tcp.h>
Socket::~Socket(){
    if(sockfd_>0){
        ::close(sockfd_);
    }
}

void Socket::bindAddress(const InetAddress&localAddr){
    struct sockaddr_in add=localAddr.getSockaddr();
   if(bind(sockfd_,(const struct sockaddr*)&add,sizeof(sockaddr_in))<0){
        LOG(FALTA,"bindAddress error!");
        exit(0);
   }
}

void Socket::listen(){
    if(::listen(sockfd_,1024)<0){
        LOG(FALTA,"listen error!");
        exit(0);
    }
    LOG(INFO,"listen success!");
}
int Socket::accept(InetAddress*peerAddr){
    struct sockaddr_in add;
    size_t len=sizeof(add);
    int connfd=::accept4(sockfd_,(sockaddr*)&add,(socklen_t*)&len,SOCK_CLOEXEC|SOCK_NONBLOCK);
    if(connfd<0){
        LOG(WARNING,"accept fd error!");
    }
    else{
        peerAddr->setAddr(add);
        LOG(INFO,"accept_fd success!");
        return connfd;
    }
}

void Socket::shutDownWrite(){
    if(shutdown(sockfd_,SHUT_WR)<0){
        LOG(WARNING,"shutDownWrite error!");
    }
}

//是否开启nagle算法
void Socket::setTcpNoDelay(bool on){
    int optval=on;
    ::setsockopt(sockfd_,IPPROTO_TCP,TCP_NODELAY,&optval,sizeof(optval));
}
//端口复用
void Socket::setReusePort(bool on){
    int optval=on;
    ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));
}
//地址复用
void Socket::setReuseAddr(bool on){
    int optval=0;
    ::setsockopt(sockfd_,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
}
//保持长连接
void Socket::setKeepAlive(bool on){
    int optval=0;
    ::setsockopt(sockfd_,SOL_SOCKET,SO_KEEPALIVE,&optval,sizeof(optval));
}