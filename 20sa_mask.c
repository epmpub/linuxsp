
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

void handler(int sig)
{
    printf("recv sig %d\n",sig);
    sleep(2);
}


int main(int argc, char const *argv[])
{
  
    struct sigaction act;
    act.sa_handler = handler;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    act.sa_flags = 0;

    if(sigaction(SIGINT,&act,NULL)<0)
        ERR_EXIT("sigaction error");
    for(;;)
        pause();
    return 0;
}
