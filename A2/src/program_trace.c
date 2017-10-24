/*question1*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int arg, char * argv []){
    int i, j, p;
    int ppid;
    ppid = getpid();
    for (i = 0; i < 3; i ++)
        if ((p =fork ()) == 0){
			printf("PARENT>%d Child>%d\n", getppid(), getpid());
            printf( "i = %d \n", i);
			j = 0;
            while ((j < i) && ((p = fork ()) == 0)){
                j ++;
				printf("PARENT>%d Child>%d\n", getppid(), getpid());
            }
            /*wait desendants*/
			if (p > 0)
                wait(0);

            if (p == 0)
                printf ( "j = %d \n", j);
            exit(j);

        }/*if*/
    
    /*wait for children*/
    if (getpid()==ppid){
        for (i=0;i<3;i++){
			wait(0);
        }
    }
    return (0);

}
