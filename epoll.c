#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_EVENTS 5
#define READ_SIZE 5

void handle_read(int fd)
{
    char buffer[READ_SIZE + 1];
    int bytes_read = read(fd, buffer, READ_SIZE);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("Read from fd %d: %s\n", fd, buffer);
    }
    else if (bytes_read == 0)
    {
        printf("EOF on fd %d\n", fd);
    }
    else
    {
        perror("read");
    }
}

int main()
{
    int epoll_fd;
    struct epoll_event event, events[MAX_EVENTS];

    umask(0);
    int monitor_file = open("test.txt", O_WRONLY | O_CREAT, 0755);

    // Create an epoll instance
    epoll_fd = epoll_create1(0);

    // Add stdin to the epoll instance
    event.events = EPOLLIN | EPOLLPRI;
    event.data.fd = monitor_file;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    while (1)
    {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].events & (EPOLLIN| EPOLLPRI))
            {
                handle_read(events[i].data.fd);
            }
        }
    }

    close(monitor_file);
    close(epoll_fd);

    return 0;
}
