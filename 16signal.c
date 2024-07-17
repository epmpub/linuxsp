
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)


void handler(int sig)
{
    printf("recv signal %d\n",sig);
    signal(SIGINT,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);

}


int main(int argc, char const *argv[])
{
    if (signal(SIGINT,handler) == SIG_ERR)
        ERR_EXIT("signal");

    while (1)
    {
        printf("loop\n");
        sleep(1);
    }
    
    return 0;
}
