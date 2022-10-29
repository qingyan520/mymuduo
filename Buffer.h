#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<unistd.h>
#include<sys/uio.h>
using std::vector;
using std::string;

class Buffer{
    public:
    static const size_t KCheapPrepend=8;
    static const size_t KInitialSize=1024;
    explicit Buffer(size_t initialsize=KInitialSize):
    buffer_(KCheapPrepend+initialsize),
    readerIndex_(KCheapPrepend),
    writerIndex_(KCheapPrepend){

    }

    //返回可读字符串长度
    size_t readableBytes()const{
        return writerIndex_-readerIndex_;
    }

    //返回可写字符串长度
    size_t writeableBytes()const{
        return buffer_.size()-writerIndex_;
    }

    //
    size_t prependable() const{
        return readerIndex_;
    }

    //返回可读缓冲区起始位置
    const char*peek()const{
        return begin()+readerIndex_;
    }

    void retrieve(size_t len){
        if(len<readableBytes())
        {
            readerIndex_+=len; //应用只读取了len长度的字节，还没有到达可读缓冲区的末尾
        }
        else
        {
            //此时应用程序读取完毕了读缓冲区中的所有数据，进行复位操作
            retrieveAll();
        }
    }

    void retrieveAll(){
        readerIndex_=writerIndex_=KCheapPrepend;
    }

    //把onMessage函数上报的所有数据，转化为string
    string retrieveAllString(){
        return retrieveAsString(readableBytes());
    }

    string retrieveAsString(size_t len){
        string result(peek(),len);
        retrieve(len);
        return result;
    }

    void ensureWritAbleBytes(size_t len){
        if(writeableBytes()<len)
        {
            makeSpace(len);  //内存不见不够，进行扩容
        }
    }


    //把[data,data+len]内存上的数据写入到写缓冲区中
    void append(const char*data,size_t len){
        ensureWritAbleBytes(len);
        std::copy(data,data+len,beginWrite());
        writerIndex_+=len;
    }

    char*beginWrite(){
        return begin()+writerIndex_;
    }
    const char*beginWrite()const{
        return begin()+writerIndex_;
    }

    ssize_t readFd(int fd,int*saveErrno);
    ssize_t writeFd(int fd,int*saveErrno);

    private:
    //返回buffer的起始地址
    char*begin(){
        return &(*buffer_.begin());
    }

    const char*begin()const{
       return &(*buffer_.begin());
    }

    void makeSpace(size_t len){
        if(writeableBytes()+prependable()<len+KCheapPrepend){
            buffer_.resize(writerIndex_+len);
        }
        else{
            size_t readable=readableBytes();
            std::copy(begin()+readerIndex_,begin()+writerIndex_,begin()+KCheapPrepend);
            readerIndex_=KCheapPrepend;
            writerIndex_=readerIndex_+readable;
        }
    }

    std::vector<char>buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};