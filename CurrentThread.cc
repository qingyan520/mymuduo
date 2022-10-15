#include"CurrentThread.h"

namespace CurrentThread{
  __thread pid_t t_cachedTid;
  void cacheTid(){
    if(t_cachedTid==0){
      t_cachedTid=static_cast<pid_t>(SYS_gettid);
    }
  }
}
