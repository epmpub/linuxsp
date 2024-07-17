
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
       #include <sys/types.h>
       #include <unistd.h>


#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)


void handler(int sig)
{
    printf("recv signal %d\n",sig);

}


int main(int argc, char const *argv[])
{
    if (signal(SIGUSR1,handler) == SIG_ERR)
        ERR_EXIT("signal");
    pid_t pid = fork();

    if (pid == -1)
        ERR_EXIT("fork");
    if (pid ==0)
    {
        kill(getppid(),SIGUSR1);
        exit(EXIT_SUCCESS);
    }

    //防止sleep被信号中断 man 3 sleep
    // DESCRIPTION
    //    sleep() causes the calling thread to sleep either until the number of real-time seconds specified in seconds have elapsed or until a signal arrives which is not ignored.

    // RETURN VALUE
    //    Zero if the requested time has elapsed, or the number of seconds left to sleep, if the call was interrupted by a signal handler.

    int n=5;
    do
    {
        n = sleep(n);
    } while (n > 0);
    return 0;
}
