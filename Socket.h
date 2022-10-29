#pragma once
#include"InetAddress.h"

class Socket{
    public:
    Socket(int fd):sockfd_(fd){}
    ~Socket();
    int fd()const{return sockfd_;}   
    void bindAddress(const InetAddress&localAddr);
    void listen();
    int accept(InetAddress*peerAddr);

    void shutDownWrite();

    void setTcpNoDelay(bool on);
    void setReusePort(bool on);
    void setReuseAddr(bool on);
    void setKeepAlive(bool on);

    private:
    const int sockfd_;
};