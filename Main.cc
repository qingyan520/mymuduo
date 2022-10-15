#include"Timestamp.h"
#include"InetAddress.h"
#include<iostream>
#include"Log.h"
int main()
{
  std::cout<<Timestamp::now().toString()<<std::endl;
  InetAddress addr(80);
  std::cout<<addr.toIpPort()<<std::endl;
  InetAddress adds(8080,"39.105.98.201");
  std::cout<<adds.toIpPort()<<std::endl;
  LOG(DEBUG,"hello");
  LOG(INFO,"你好");
  return 0;
}
