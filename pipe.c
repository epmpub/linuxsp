#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int main() {
    int pipe_fd[2];
    pid_t pid;
    char write_msg[BUFFER_SIZE] = "Hello from child process!";
    char read_msg[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipe_fd[0]); // Close unused read end

        // Write to the pipe
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);
        close(pipe_fd[1]); // Close write end after writing

        printf("Child: Wrote message to pipe\n");
    } else { // Parent process
        close(pipe_fd[1]); // Close unused write end

        // Read from the pipe
        read(pipe_fd[0], read_msg, BUFFER_SIZE);
        close(pipe_fd[0]); // Close read end after reading

        printf("Parent: Read message from pipe: %s\n", read_msg);
    }

    return 0;
}
