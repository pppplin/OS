#include <process.h>


void recursive_fork(int n){
    int pid;
    pid = fork();
    if (pid<0){
        perror("error\n");
        exit(1);
    }else if (pid==0){
        printf("CHILD(%d)\n", getpid());
        exit(1);
    }

    if (n>1){
        recursive_fork(n-1);
    }
}


