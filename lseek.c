#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char const *argv[])
{
    int in_fd = open(argv[1],O_RDONLY);
    off_t size = lseek(in_fd,0,SEEK_END);
    printf("file size is:%ld\n",size);
    return 0;
}
