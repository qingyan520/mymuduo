#include<unistd.h>
#include<sys/syscall.h>
namespace CurrentThread{
  extern __thread pid_t t_cachedTid;
  void cacheTid();
  inline int tid(){
    if(__builtin_expect(t_cachedTid==0,0)){
      cacheTid();
    }
    return t_cachedTid;

  }
}
