#define XOPEN_SOURCE 700

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int c = 0;
//mask so that only deliver once.
void sig_handler(int sig){
    c++;
    printf("Current value of counter:%d \n", c);
} 

int main (int argc, char* argv []) {
    
    sigset_t  sig_rec ;	/* list of blocked singals */
    sigset_t  sig_pend;	/* list of pending signals */
    
    struct sigaction act;
    
    sigfillset(&sig_rec);
    sigprocmask (SIG_SETMASK, &sig_rec, NULL);

    act.sa_mask = sig_rec;
    act.sa_flags = 0;
    act.sa_handler = sig_handler;

    sigaction(SIGINT, &act, 0);

    sigemptyset (&sig_rec);
    sigaddset (&sig_rec,SIGINT);
    sigaddset (&sig_rec,SIGQUIT);
 
    /* mask SIGINT and SIGQUIT */
    sigprocmask (SIG_SETMASK, &sig_rec,NULL);
    
    sleep (5);
    
    /* retrieve pending signals */
    sigpending (&sig_pend);
    if (sigismember ( &sig_pend,SIGINT) )
        printf("SIGINT received\n");
    if (sigismember ( &sig_pend,SIGQUIT) )
        printf("SIGQUIT received\n");
    
    sigdelset (&sig_rec,SIGINT);
    sigdelset (&sig_rec,SIGQUIT);
    sigprocmask (SIG_SETMASK, &sig_rec,NULL);
    
    printf("Final value of counter:%d \n", c);
    printf ("End program \n");
    
    return EXIT_SUCCESS;
}


