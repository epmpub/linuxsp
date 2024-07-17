#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>


int main(int argc, char const *argv[])
{
    struct dirent *dirp;
    DIR* dir = opendir(".");

    while ((dirp = readdir(dir)) != NULL)
    {
        if (strncmp(dirp->d_name,".",1) != 0)
        {
            printf("%s\n",dirp->d_name);
        }
    }

    closedir(dir);
    return 0;
}
