
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
    mqid = mq_open("/abc",O_RDONLY);
    if (mqid == (mqd_t)-1)
    {
        ERR_EXIT("mqopen");
    }
    printf("open mq OK\n");

    struct mq_attr attr;
    mq_getattr(mqid,&attr);

    printf("max number os msg = %ld ,max bytes/msg %ld, current on queue %ld\n",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

    mq_close(mqid);
    
    return 0;
}
