#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    assert(argc >= 2);
    const char *filepath = argv[1];

    int fd = open(filepath, O_RDONLY);
    assert(fd >= 0);

    struct stat statbuf;
    int err = fstat(fd,&statbuf);
    assert(err >= 0);

    void* ptr = mmap(NULL,statbuf.st_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE,
            fd,0);
    assert(ptr != MAP_FAILED);
    close(fd);

    ssize_t n = write(1,ptr,statbuf.st_size);
    assert(n == statbuf.st_size);

    err = munmap(ptr,statbuf.st_size);
    assert(err >= 0);
    return 0;
}
