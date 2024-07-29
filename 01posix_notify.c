
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

typedef struct stu
{
    char name[32];
    int age;
} STU;

mqd_t mqid;
struct sigevent sigev;

void handle_SIGUSER1(int sig)
{
    if (mq_notify(mqid, &sigev) == (mqd_t)-1)
    {
        ERR_EXIT("notify setup");
    }

    printf("got signal number is:%d\n", sig);

    struct mq_attr attr;
    mq_getattr(mqid, &attr);

    STU stu;
    if (mq_receive(mqid, (char *)&stu, attr.mq_msgsize, 0) == 0)
    {
        ERR_EXIT("mq send");
    }

    printf("recv stu name = %s age=%d \n", stu.name, stu.age);
}

int main(int argc, char const *argv[])
{
    // mqd_t mqid;
    mqid = mq_open("/abc", O_RDONLY);
    if (mqid == (mqd_t)-1)
    {
        ERR_EXIT("mqopen");
    }
    printf("open mq OK\n");

    signal(SIGUSR1, handle_SIGUSER1);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;

    if (mq_notify(mqid, &sigev) == (mqd_t)-1)
    {
        ERR_EXIT("notify setup");
    }

    for (;;)
        pause();

    mq_close(mqid);

    return 0;
}
