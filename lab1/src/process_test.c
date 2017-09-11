#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <process.h>

#define N_CHILDREN 10

int main (int argc, char * argv []) {
    int pid;
    /*recursive_fork(N_CHILDREN);*/
    for (int i=0; i<N_CHILDREN; i++){
        pid = fork();
        if (pid < 0){
            perror("error\n");
            exit(1);
        }else if (pid==0){
            printf("child(%d): %d \n", i+1,  getpid());
            exit(1);
        }
    
        /*exactly one child*/
        if (i==0)
            wait(0);
        /*last child created*/
        if (i==N_CHILDREN-1)
            wait(0);
        /*all children*/
        if (i=0)
            for (int j=0;j<N_CHILDREN;j++){
                wait(0);
            }
    }
    return 0;
}







