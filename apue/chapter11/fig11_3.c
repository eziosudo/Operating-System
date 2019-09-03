#include "apue.h"
#include <pthread.h>

/**
 * 屏障。pthread_join()函数，以阻塞的方式等待thread指定的线程结束。
 */

void *thr_fn1(void *arg) {
    printf("thread 1 returning\n");
    pthread_t tid = pthread_self();
    printf("tid1 %lu (0x%lx)\n",
           (unsigned long)tid, (unsigned long)tid);
    return ((void *) 1);
}

void *thr_fn2(void *arg) {
    printf("thread 2 exiting\n");
    pthread_t tid = pthread_self();
    printf("tid2 %lu (0x%lx)\n",
           (unsigned long)tid, (unsigned long)tid);
    pthread_exit((void *) 2);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    void *tret;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        exit(err);
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        exit(err);

    //如果没有thread_join，则无法确定哪个线程先结束
    //有可能主线程先结束，其他线程没有跑完就被终止了

    //当一个线程通过pthread_exit退出或简单得从启动例程返回时，
    // 其他线程可以通过pthread_join函数获得该线程的退出状态，并且把退出状态保存到tret
    err = pthread_join(tid1, &tret);
    if (err != 0)
        exit(err);
    printf("thread 1 exit code %ld\n", (long) tret);
    err = pthread_join(tid2, &tret);
    if (err != 0)
        exit(err);
    printf("thread 2 exit code %ld\n", (long) tret);
    exit(0);
}
