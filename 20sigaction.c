
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
    printf("recv a sig = %d\n", sig);
}


int main(int argc, char const *argv[])
{
    printf("hello\n");
    struct sigaction  act = {0} ;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (sigaction(SIGINT,&act,NULL)<0)
       ERR_EXIT("sigaction error");

    for(;;)
        pause();
    return 0;
}
