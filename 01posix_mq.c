
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

int main(int argc, char const *argv[])
{
    mqd_t mqid;
    mqid = mq_open("/abc",O_CREAT | O_RDWR,0666,NULL);
    if (mqid == (mqd_t)-1)
    {
        ERR_EXIT("mqopen");
    }
    printf("OK");

    mq_close(mqid);
    
    return 0;
}
