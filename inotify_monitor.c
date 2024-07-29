#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <limits.h>
#include <errno.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void handle_event(struct inotify_event *event) {
    if (event->mask & IN_MODIFY) {
        printf("File %s  %d was modified.\n", event->name,event->wd);
    }
}

int main() {
    int inotify_fd, wd;
    char buf[BUF_LEN];
    ssize_t num_read;
    char *p;

    // Create an inotify instance
    inotify_fd = inotify_init1(IN_NONBLOCK);
    if (inotify_fd == -1) {
        perror("inotify_init1");
        exit(EXIT_FAILURE);
    }

    // Add a watch for the test.txt file
    wd = inotify_add_watch(inotify_fd, "test.txt", IN_MODIFY);
    if (wd == -1) {
        perror("inotify_add_watch");
        close(inotify_fd);
        exit(EXIT_FAILURE);
    }

    printf("Monitoring file: test.txt\n");

    while (1) {
        num_read = read(inotify_fd, buf, BUF_LEN);
        if (num_read == 0) {
            continue;
        }
        if (num_read == -1) {
            if (errno == EAGAIN) {
                continue;
            } else {
                perror("read");
                break;
            }
        }

        for (p = buf; p < buf + num_read; ) {
            struct inotify_event *event = (struct inotify_event *) p;
            handle_event(event);
            p += sizeof(struct inotify_event) + event->len;
        }
    }

    // Clean up
    close(wd);
    close(inotify_fd);

    return 0;
}
