#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
          #include <sys/sendfile.h>


// #define ERR_EXIT(m) (perror(m),exit(EXIT_FAILURE))

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    } while (1)

int main(int argc, char const *argv[])
{
    umask(0);
    int src;
    src = open(argv[1], O_RDONLY);
    if (src == -1)
    {
        // fprintf(stderr, "open file error with :%s \n", strerror(errno));
        // perror("open file error");
        // exit(EXIT_FAILURE);
        ERR_EXIT("open src file err");
    }
    char buffer[1024];
    int ret = read(src, buffer, 1024);
    if (ret == -1)
    {
        ERR_EXIT("read src file");
    }
    printf("first read counter is:%d\n", ret);

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (dest == -1)
    {
        ERR_EXIT("create dest file");
    }

    // Get the size of the source file
    off_t file_size = lseek(src, 0, SEEK_END);
    lseek(src, 0, SEEK_SET);


    ret = sendfile(dest, src, NULL, file_size);
    if (ret == -1)
    {
       ERR_EXIT("sendfile");
    }
    
    close(src);
    close(dest);
    return 0;
}
