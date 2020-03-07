##POSIX function
* pthread_create
* pthread_join    //wait for the thread return pointer (use void*)
* pthread_detach  //set thread to releae the resources

* pthread_kill    //send a signal
* pthread_self    //get pthread_t to get the id

* pthread_cancel  // terminate another thread
* pthread_exit    // exit a thread without exiting process
**Don't use exit leave the thread, it may kill the process

##pthread_join
* In main thread to use pthread_join to wait for the thread result.
* Thread can allocate memory and return the pointer but main thread need to free the memory.



##Kernel Thread and User Threads
*Kernel thread: ps -aux with [] process
*驅動程式控制in kernel thread 避免system call的overhead

##pthread attribuite 詳解
###pthread_attr_t
```
typedef struct
{
   int                       detachstate;     //线程的分离状态
   int                       schedpolicy;     //线程调度策略
   struct sched_param        schedparam;      //线程的调度参数
   int                       inheritsched;    //线程的继承性
   int                       scope;           //线程的作用域
   size_t                    guardsize;       //线程栈末尾的警戒缓冲区大小
   int                       stackaddr_set;
   void *                    stackaddr;       //线程栈的位置
   size_t                    stacksize;       //线程栈的大小
}pthread_attr_t;
```
###init & destroy
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

###detachstate
detachstate：
PTHREAD_CREATE_DETACHED //set thread to releae the resources after pthread_exit
PTHREAD_CREATE_JOINABLE //default use pthread_join to wait the return
```
int pthread_attr_getdetachstate(const pthread_attr_t * attr, int * detachstate);
int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
```


