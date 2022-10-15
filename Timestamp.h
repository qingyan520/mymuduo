#pragma once
#include<string>
#include<time.h>
class Timestamp{
  public:
    Timestamp():mic_(0){

    }
    explicit Timestamp(int64_t mic):mic_(mic){

    }
    
    static Timestamp now(){
      return Timestamp(time(nullptr));
    }

    std::string toString()const {
      struct tm*ttime;
      ttime=localtime(&mic_);
      char now[30]={0};
      strftime(now, 1024, "%Y-%m-%d %H:%M:%S", ttime);
      return now;
    }

  private:
    int64_t mic_;
};
