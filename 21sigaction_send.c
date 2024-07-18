
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
    if (argc != 2)
    {
        fprintf(stderr," Usage %s pid \n",argv[0]);
        ERR_EXIT(EXIT_FAILURE);
    }
    
    pid_t pid = atoi(argv[1]);
    union sigval v;
    v.sival_int = 100;


    sigqueue(pid,SIGINT,v);
    sigqueue(pid,SIGINT,v);
    sigqueue(pid,SIGINT,v);


    sigqueue(pid,SIGRTMIN+1,v); 
    sigqueue(pid,SIGRTMIN+1,v);
    sigqueue(pid,SIGRTMIN+1,v);

    sleep(3);
    kill(pid,SIGUSR1);
    kill(pid,SIGUSR1);
    kill(pid,SIGUSR1);

    return 0;
}

