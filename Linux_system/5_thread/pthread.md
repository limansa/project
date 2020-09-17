## POSIX function
* pthread_create
* pthread_join    //wait for the thread return pointer (use void*)
* pthread_detach  //set thread to releae the resources

* pthread_kill    //send a signal
* pthread_self    //get pthread_t to get the id

* pthread_cancel  // terminate another thread
* pthread_exit    // exit a thread without exiting process
**Don't use exit leave the thread, it may kill the process
* pthread_setname_np //set the thread name

## pthread_join
* In main thread to use pthread_join to wait for the thread result.
* Thread can allocate memory and return the pointer but main thread need to free the memory.

## Kernel Thread and User Threads
*Kernel thread: ps -aux with [] process
*驅動程式控制in kernel thread 避免system call的overhead

## pthread_attr 詳解
### pthread_attr_t
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

### Default
* Deafault thread attributes:
```
    Detach state        = PTHREAD_CREATE_JOINABLE
    Scope               = PTHREAD_SCOPE_SYSTEM
    Inherit scheduler   = PTHREAD_INHERIT_SCHED
    Scheduling policy   = SCHED_OTHER
    Scheduling priority = 0
    Guard size          = 4096 bytes
    Stack address       = 0x7f6672c71000
    Stack size          = 0x800000 bytes
```

### init & destroy
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

### detachstate
PTHREAD_CREATE_DETACHED:
    set thread to releae the resources after pthread_exit
PTHREAD_CREATE_JOINABLE:
    default use pthread_join to wait the return
```
int pthread_attr_getdetachstate(const pthread_attr_t * attr, int * detachstate);
int pthread_attr_setdetachstate(pthread_attr_t * attr, int detachstate);
```
## Reentrant and thread-safe
### Atomic operation
* 希望一次做完呵成, 中間不要被打斷. 這一類的指令是多核 CPU 必備的指令, 否則它就無法解決核與核之間對於共用資源 (周邊設備或者變數) 之間存取競爭的問題
* EX: read-modify-write, test-and-set, fetch-and-add, compare-and-swap
### Reentrant
若一個程序或子程序可以在任意時刻被中斷(ex. ISR )然後作業系統調度執行另外一段代碼，這段代碼又調用了該子程序不會出錯
* 若一個函數是可重入的，則該函數應當滿足下述條件：
不能含有Static or global variable。
不能return static or glovbal variable and pointer。
只能處理由caller提供的數據。
不能依賴於單實例模式資源的鎖。
call的函數也必需是可重入的。
* 實做要點
    * 不要使用共用資源 (global variables and static variable); 或者也可以在寫入共用變數之前, 把數值暫存在區域變數中, 使用完畢後回存.
    * 不修改自身的程式碼.
    * 不呼叫 non-reentrant 函數. 例如: clib 中的 strtok(), rand(), srand() 都是 non-reentrant, 對應的 reentrant 版本是 strtok_r(), rand_r(), srand_r().

### Thread-safe

###
* 可重入函數未必是執行緒安全的
1. Reentrant but not thread safe
一個函數打開某個文件並讀入數據。 ()
可重入：因為它的多個實例同時執行不會造成衝突；
不是執行緒安全：因為在它讀入文件時可能有別的執行緒正在修改該文件
2. Not reentrant but thread safe (執行緒安全，不可重入)
函數在它的函數體內部訪問共享資源使用了加鎖、解鎖操作
因為若該函數一個實例運行到已經執行加鎖但未執行解鎖時被停下來，系統又啟動該函數的另外一個實例，則新的實例在加鎖處將轉入等待。如果該函數是一個中斷處理服務，在中斷處理時又發生新的中斷將導致資源死鎖。

fprintf函數就是執行緒安全但不可重入。

## Thread Synchronization
* Race condition: two or more threds need the shared resource.
* Critical sections: manage share resource
* Reentrant function: 可重複進入的程式
* Thread safe



### Mutex
```
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
````
### Samaphore
sem_overview - overview of POSIX semaphores
```
#include <semaphore.h>
@argument: pshared 表示跟多少process share這個semaphore
@argument: value: 表示最多同時access resource的數量
int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t * sem);//等待signal 獲取所有權
int sem_post(sem_t * sem);//發出訊號即釋放所有權
int sem_destroy(sem_t *sem);
````