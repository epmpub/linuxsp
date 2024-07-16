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

    char buff[1024] = {0};
    read(in_fd,buff,5);
    printf("read string is:%s\n",buff);

    off_t pos = lseek(in_fd,0,SEEK_END);
    printf("current pos is:%ld\n",pos);

    return 0;
}
