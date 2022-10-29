#include"TcpConnection.h"
#include"Log.h"
#include"Socket.h"
#include"Buffer.h"
#include"Channel.h"
#include"EventLoop.h"


//检查EventLoop是否为nullptr
static EventLoop*check_not_nullptr(EventLoop*loop)
{
    if(loop==nullptr)
    {
        LOG(FALTA,"EventLoop is nullptr!");
        exit(0);
    }
    return loop;
}
TcpConnection::TcpConnection(EventLoop*loop,const std::string&name,int sockfd,const InetAddress&localAddr,const InetAddress&peerAddr):
    loop_(check_not_nullptr(loop)),
    name_(name),
    state_(StateE::kConnecting),
    reading_(true),
    socket_(new Socket(sockfd)),
    channel_(new Channel(loop,sockfd)),
    localAddr_(localAddr),
    peerAddr_(peerAddr),
    highWaterMark_(64*1024*1024){
        //给channel设置对应的回调函数，poller监听到对应的事件发送了，调用对应的回调函数进行处理
        channel_->setReadCallback(std::bind(&TcpConnection::handleRead,this,std::placeholders::_1));
        channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite,this));
        channel_->setCloseCallback(std::bind(&TcpConnection::handleClose,this));
        channel_->setErrorCallback(std::bind(&TcpConnection::handleError,this));
        
        //启动Tcp保活机制
        socket_->setKeepAlive(true);
    }


TcpConnection::~TcpConnection(){
    LOG(INFO,"TcpConnection::destory!");
}

//设置读回调
void TcpConnection::handleRead(Timestamp receiveTime){
    int saveError=0;
    ssize_t n=inputBuffer_.readFd(channel_->fd(),&saveError);
    
    if(n>0)
    {
        //已建立连接的用户有可读事件发生了，调用该用户传入的回调操作
        if(messageCallback_)
        messageCallback_(shared_from_this(),&inputBuffer_,receiveTime);
    }
    else if(n==0)
    {
        //对端关闭连接
        handleClose();
    }
    else
    {
        errno=saveError;
        LOG(WARNING,"TcpConnection::handleError!");
        handleError();
    }
}


//设置写回调
void TcpConnection::handleWrite(){
    if(channel_->isWriting()){
        int savedErrno=0;
        ssize_t n=outputBuffer_.writeFd(channel_->fd(),&savedErrno);
        if(n>0)
        {
            outputBuffer_.retrieve(n);
            if(outputBuffer_.readableBytes()==0)
            {
                channel_->disableWriting();
                
                if(writeCompleteCallback_)
                {
                    loop_->queueInLoop(std::bind(&TcpConnection::writeCompleteCallback_,shared_from_this()));
                }
                if(state_==kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else{
            LOG(WARNING,"TcpConnection::handleWrite");
        }
    }
    else
    {
        LOG(WARNING,"TcpConnection is not Writing!");
    }
}

void TcpConnection::handleClose(){
    LOG(INFO,std::to_string(channel_->fd())+":"+std::to_string(state_));
    setState(kDisconnected);
    channel_->disableAll();
    TcpConnectionPtr conPtr(shared_from_this());
    if(connectionCallback_)
    {
        connectionCallback_(conPtr);
    }
    closeCallback_(conPtr);
}

void TcpConnection::handleError(){
    int optval=0;
    socklen_t optlen=sizeof(optval);
    int err=0;
    if(::getsockopt(channel_->fd(),SOL_SOCKET,SO_ERROR,&optval,&optlen)<0)
    {
        err=errno;
    }
    else
    {
        err=optval;
    }
    LOG(WARNING,"TcpConnection::handleError#"+name_);
}


//发送应用写的快，内核发送数据慢，把待发送数据写入buf缓冲区
void TcpConnection::sendInLoop(const char*message,size_t len){
    ssize_t nwrite=0;
    size_t remaining=len;
    bool faultError=false;

    //之前调用过connection放入shutdown，不在进行发送
    if(state_==kDisconnected)
    {
        LOG(WARNING,"disconnected give no writing!");
        return ;
    }


    //channel第一次写数据，并且缓冲区没有待发送数据
    if(!channel_->isWriting()&&outputBuffer_.readableBytes()==0)
    {
        int saveError=0;
        nwrite=::write(channel_->fd(),message,len);

        if(nwrite>=0)
        {
            remaining=len-nwrite;    //剩余待发送数据
            if(remaining==0&&writeCompleteCallback_)
            {
                LOG(INFO,"send message to "+std::to_string(channel_->fd())+"success!");
                //数据全部发送完成，就不用给channel设置epollout事件
                loop_->queueInLoop(std::bind(&TcpConnection::writeCompleteCallback_,shared_from_this()));
            }
        }
        else
        {
            nwrite=0;
            if(errno!=EWOULDBLOCK)
            {
                LOG(WARNING,"TcpConnection::sendInLoop");
                if(errno==EPIPE||errno==ECONNRESET)
                {
                    faultError=true;
                }
            }
        }

        //当前write没有把数据发送完，剩余的数据缓存到缓冲区中
        //注册epollout事件，poller发现tcp缓冲区有空间，就会通知相应的channel-sock，然后指向writeCallback发送数据
        //把缓冲区数据发送完成
        if(!faultError&&remaining>0)
        {
            size_t oldlen=outputBuffer_.readableBytes();
            if(oldlen+remaining>=highWaterMark_
            &&oldlen<highWaterMark_&&
            highWatermarkCallback_)
            {
                loop_->queueInLoop(std::bind(highWatermarkCallback_,shared_from_this(),oldlen+remaining));
            }
            outputBuffer_.append(message+nwrite,remaining);
            if(!channel_->isWriting())
            {
                channel_->enableWriting();
            }

        }
    }

    //说明当前这一次write，并没有把数据全部发送出去，剩余的数据需要保存到缓冲区中，然后给channel
    //注册epollout事件，poller发现tcp缓冲区有空间，会通知sock-channel，调用writeCallback回调
    if(!faultError&&remaining>0)
    {
        channel_->enableWriting();
    }
}


void TcpConnection::send(const string&buf){
    if(state_==kConnected)
    {
        if(loop_->isInLoopThread())
        {
            LOG(INFO,"send data to:"+std::to_string(channel_->fd()));
          //  std::cout<<buf.c_str()<<":"<<buf.size()<<std::endl;
            sendInLoop(buf.c_str(),buf.size());
        }
         else
        {
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop,this,buf.c_str(),buf.size()));

        }
    }
}


//建立连接
void TcpConnection::connectEstablished(){
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading();        //向epoller注册epollin事件
    LOG(INFO,"TcpConnection has connected:"+std::to_string(channel_->fd()));
    if(connectionCallback_)
    connectionCallback_(shared_from_this());
}

//连接销毁
void TcpConnection::connectDestroyed()
{
    if(state_==kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll();
    }
    channel_->remove();   //channel从poller中删除掉
}


void TcpConnection::shutdown(){
    if(state_==kConnected)
    {
        setState(StateE::kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop,this));

    }
}

void TcpConnection::shutdownInLoop(){
    //当前outputBuffer中的数据已经发送完成了
    if(!channel_->isWriting())
    {
        socket_->shutDownWrite();
    }
}

