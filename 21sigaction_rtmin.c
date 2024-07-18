
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
    struct sigaction act = {0};
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigaddset(&s, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &s, NULL);

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction  SIGINT error");

    if (sigaction(SIGRTMIN+1, &act, NULL) < 0)
        ERR_EXIT("sigaction  SIGRTMIN error");

    if (sigaction(SIGUSR1, &act, NULL) < 0)
        ERR_EXIT("sigaction  SIGRTMIN error");

    for (;;)
        pause();
    return 0;
}

void handler(int sig, siginfo_t *info, void *ctx)
{
    if (sig == SIGINT || sig == SIGRTMIN+1)
    {
        printf("recv as sig %d data=%d\n", sig, info->si_value.sival_int);
    }
    else if (sig == SIGUSR1)
    {
        printf("recv as sig %d data=%d\n", sig, info->si_value.sival_int);
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGINT);
        sigaddset(&s, SIGRTMIN+1);
        sigprocmask(SIG_UNBLOCK, &s, NULL);
    }
}