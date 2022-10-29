#include"TcpServer.h"
#include"EventLoop.h"
class echo_server
{
  public:
  echo_server(EventLoop*loop,InetAddress&addr,const string&name):
  svr_(loop,addr,name),
  loop_(loop)
  {
      svr_.setMessageCallback(std::bind(&echo_server::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
      svr_.setConnectionCallback(std::bind(&echo_server::onConnection,this,std::placeholders::_1));    
      svr_.setThreadNum(3);
  }
  void start()
  {
    svr_.start();
  }
  private:
  void onConnection(const TcpConnectionPtr&conn)
  {
    if(conn->connected())
    {
      std::cout<<"TcpConnection has connected from "<<conn->peerAddress().toIpPort()<<std::endl;
    }
  }
  void onMessage(const TcpConnectionPtr&conn,Buffer*buf,Timestamp time)
  {
    std::cout<<buf->retrieveAllString()<<std::endl;
    conn->send(buf->retrieveAllString());
  }
  TcpServer svr_;
  EventLoop*loop_;
};
int main()
{
  EventLoop loop;
  InetAddress addr(8888,"172.16.47.167");
  string name="hello";
  echo_server svr(&loop,addr,name);

  svr.start();
  loop.loop();
  return 0;
}
