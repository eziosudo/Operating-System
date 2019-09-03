#include "apue.h"

int globvar = 6;        /* external variable in initialized data */
char buf[] = "a write to stdout\n";

int
main(void) {
    int var;        /* automatic variable on the stack */
    pid_t pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
//        err_sys("write error");
        exit(-1);
    printf("before fork\n");    /* we don't flush stdout */

    if ((pid = fork()) < 0) {
//        err_sys("fork error");
        exit(-1);
    } else if (pid == 0) {        /* 返回pid = 0 是子进程 */
        globvar++;                /* modify variables */
        var++;
    } else {
        sleep(2);                /* 如果是父进程，等待2s */
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long) getpid(), globvar,
           var);
    exit(0);
}
