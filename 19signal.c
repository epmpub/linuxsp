
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
    if (sig == SIGINT)
    {
        printf("recv a sig = %d\n", sig);
    }
}

void printsigset(sigset_t *set)
{
    int i;
    for (i = 0; i < _NSIG; ++i)
    {
        if (sigismember(set, i))
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    sigset_t pset;
    sigset_t bset;
    sigemptyset(&bset);
    sigaddset(&bset,SIGINT);

    if (signal(SIGINT, handler) == SIG_ERR)
        ERR_EXIT("signal error");
    
    sigprocmask(SIG_BLOCK,&bset,NULL);
    
    for (;;)
    {
        sigpending(&pset);
        printsigset(&pset);
        sleep(1);
    }

    return 0;
}
