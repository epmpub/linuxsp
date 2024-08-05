#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

// #define ERR_EXIT(m) (perror(m),exit(EXIT_FAILURE))

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (1)

typedef struct std
{
    char name[4];
    int age;
} STU;

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage:%s <File>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    fd = open(argv[1], O_RDWR, 0666);
    if (fd == -1)
    {
        ERR_EXIT("open");
    }

    STU *p;
    p = (STU *)mmap(NULL, sizeof(STU) * 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == NULL)
    {
        ERR_EXIT("mmap");
    }

    for (int i = 0; i < 10; i++)
    {
        printf("name = %s,age=%d\n",(p+i)->name,(p+i)->age);
    }
    munmap(p, sizeof(STU) * 10);

    return 0;
}
