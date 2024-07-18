
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

void handler(int, siginfo_t *, void *);


int main(int argc, char const *argv[])
{
    printf("hello\n");
    struct sigaction  act = {0} ;
    act.sa_sigaction = handler;

    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGRTMIN,&act,NULL)<0)
       ERR_EXIT("sigaction error");

    for(;;)
        pause();
    return 0;
}

void handler(int sig, siginfo_t *info, void *ctx)
{
    if (sig == SIGINT)
    {
            printf("recv as sig %d data=%d\n",sig,info->si_value.sival_int);
    }else if (sig == SIGRTMIN)
    {
        printf("recv as sig %d data=%d\n",sig,info->si_value.sival_int);
    }
    
}