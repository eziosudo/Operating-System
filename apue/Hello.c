

#include "apue.h"

int main(){
    printf("hello from process ID %ld\n", (long)getpid());
    exit(0);
}