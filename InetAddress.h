#pragma once 
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>
class InetAddress{
  public:
    InetAddress(int16_t port=0,std::string ip="127.0.0.1"){
      addr_.sin_family=AF_INET;
      addr_.sin_port=htons(port);
      addr_.sin_addr.s_addr=inet_addr(ip.c_str());
    }

    explicit InetAddress(const InetAddress&addr){
      addr_.sin_family=addr.addr_.sin_family;
      addr_.sin_port=addr.addr_.sin_port;
      addr_.sin_addr.s_addr=addr.addr_.sin_addr.s_addr;
    }

    InetAddress(const sockaddr_in&addr)
    {
      addr_.sin_addr.s_addr=addr.sin_addr.s_addr;
      addr_.sin_port=addr.sin_port;
      addr_.sin_family=addr.sin_family;
    }

    std::string toPort()const {
      return std::to_string(ntohs(addr_.sin_port));
    }
    
    std::string toIp()const{
      return inet_ntoa(addr_.sin_addr);
    }
    
    std::string toIpPort()const{
      return toIp()+":"+toPort();
    }

   struct sockaddr_in getSockaddr() const{
      return  addr_;
    }

    void setAddr(struct sockaddr_in addr){
      addr_=addr;
    }
  private:
    struct sockaddr_in addr_;
};
