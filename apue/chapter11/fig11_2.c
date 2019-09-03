#include "apue.h"
#include <pthread.h>

/**
 * 创建线程时打印进程和线程ID
 */

pthread_t ntid;

void printids(const char *s) {
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    //lu: 十进制  lx: 十六进制
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long) pid,
           (unsigned long) tid, (unsigned long) tid);
}

void *thr_fn(void *arg) {
    printids("new thread: ");
    return ((void *) 0);
}

int main(void) {
    int err;
    /**
     * pthread_create成功返回时
     * 第一个参数：新创建线程的线程ID会被设置成ntid指向的内存单元
     * 第二个参数：线程属性
     * 第三个参数：新创建的线程从thr_fn函数的地址开始运行
     * 第四个参数：
     *
     */
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
        _exit(err);
//        err_exit(err, "can't create thread");
    printids("main thread:");
    sleep(1);
    exit(0);
}
