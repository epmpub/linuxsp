
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

typedef struct stu
{
    char name[32];
    int age;
} STU;

int main(int argc, char const *argv[])
{

    umask(0);
    int shmid;
    shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
    if (shmid == -1)
    {
        ERR_EXIT("shm open");
    }
    printf("shm_open OK\n");

    STU stu;
    strcpy(stu.name,"wang LEE");
    stu.age = 100;

    assert(sizeof(stu) == sizeof(STU));

    if (ftruncate(shmid, sizeof(stu)) == -1)
    {
        ERR_EXIT("ftruncate");
    }

    struct stat buf;
    if(fstat(shmid,&buf) == -1)
    {
        ERR_EXIT("fstat");
    }

    printf("size = %ld,mode=%o \n",buf.st_size,buf.st_mode & 07777);
    close(shmid);
    return 0;
}
