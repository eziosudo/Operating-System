

#include "apue.h"
#include <pthread.h>

int main(){
    printf("hello from process ID %ld\n", (long)getpid());
    pthread_t p = pthread_self();
    printf("thread ID %ld\n", p);
    exit(0);
}

