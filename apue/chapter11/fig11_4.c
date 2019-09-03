#include "apue.h"
#include <pthread.h>

struct foo {
    int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp) {
    printf("%s", s);
    printf("  structure at 0x%lx\n", (unsigned long) fp);
    //（MacOS）第二个线程再次访问时，fp已经被清空，得到SIGSEGV信号（segment fault, 访问无效内存）
    //此处实现与具体操作系统有关
    printf("  foo.a = %d\n", fp->a);
    printf("  foo.b = %d\n", fp->b);
    printf("  foo.c = %d\n", fp->c);
    printf("  foo.d = %d\n", fp->d);
}

void *thr_fn1(void *arg) {
    printf("thread 1: ID is %lu (0x%lx)\n", (unsigned long) pthread_self(), (unsigned long) pthread_self());
    struct foo foo = {1, 2, 3, 4};

    printfoo("thread 1:\n", &foo);
    pthread_exit((void *) &foo);
}

void *thr_fn2(void *arg) {
    printf("thread 2: ID is %lu (0x%lx)\n", (unsigned long) pthread_self(), (unsigned long) pthread_self());
    pthread_exit((void *) 0);
}

int main(void) {
    int err;
    pthread_t tid1, tid2;
    struct foo *fp;

    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        exit(err);

    //pthread_join会等到线程退出，此时线程资源也被回收，系统可以在同样地址上创建第二个线程
    err = pthread_join(tid1, (void *) &fp);
    if (err != 0)
        exit(err);
    sleep(1);
    printf("parent starting second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        exit(err);
    sleep(1);
    printfoo("parent:\n", fp);
    exit(0);
}
