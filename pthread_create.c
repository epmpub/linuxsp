#include <pthread.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>    /* For O_* constants */
#include <sys/stat.h> /* For mode constants */
#include <mqueue.h>

#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /* For O_* constants */

#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (0)

void* thread_routine(void *arg)
{
    for (int i = 0; i < 20; i++)
    {
        printf("B");
        fflush(stdout);
        if (i == 3 )
        {
            pthread_exit("XYZ");
        }
        
    }
    return (char*)"ABC";
}

int main(int argc, char const *argv[])
{
    pthread_t tid;
    int ret;
    if ((ret = pthread_create(&tid, NULL, thread_routine, NULL)) != 0)
    {
        fprintf(stderr, "pthread_create %s\n", strerror(ret));
        ERR_EXIT("pthread_create");
    }
    for (int i = 0; i < 20; i++)
    {
        printf("A");
        fflush(stdout);
    }
    void* retval;
    pthread_join(tid,&retval);
    printf("retval is %s\n",(char*)retval);
    return 0;
}
