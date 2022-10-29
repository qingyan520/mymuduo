#include"Buffer.h"

 ssize_t Buffer::readFd(int fd,int*saveErrno){
    char extrabuff[65536]={0};
    struct iovec iov[2];
    size_t writeable=writeableBytes();
    iov[0].iov_base=beginWrite();
    iov[0].iov_len=writeableBytes();
    iov[1].iov_base=extrabuff;
    iov[1].iov_len=sizeof(extrabuff);

    int iovcnt=(writeable<sizeof(extrabuff))? 2:1;

    int n=readv(fd,(const iovec*)&iov,iovcnt);

    if(n<0){
        *saveErrno=errno;
    }
    else if(n<writeable){
        writerIndex_+=n;
    }
    else{
        //此时extrabuffer上面也写了数据，我们需要读取extrabuffer的长度然后再写入到buffer中
        writerIndex_=buffer_.size();
        Buffer::append(extrabuff,n-writeable);
    }
    return n;
}

ssize_t Buffer::writeFd(int fd,int*saveErrno){
    ssize_t n=write(fd,peek(),readableBytes());
    if(n<0)
    {
        *saveErrno=errno;
    }
    return n;
}