#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// #define ERR_EXIT(m) (perror(m),exit(EXIT_FAILURE))

#define ERR_EXIT(m) do { perror(m); exit(EXIT_FAILURE);} while(1)

int main(int argc, char const *argv[])
{
    umask(0);
    int fd;
    fd = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR);
    if (fd == -1)
    {
        // fprintf(stderr, "open file error with :%s \n", strerror(errno));
        // perror("open file error");
        // exit(EXIT_FAILURE);
        ERR_EXIT("open file err");
    }
    const char msg[] = "hello world\r\n";
    ssize_t count = write(fd,msg,sizeof(msg));
    if (count != sizeof(msg))
    {
        ERR_EXIT("write file err");
    } 
    close(fd);
    printf("open successfully\n");

    return 0;
}
