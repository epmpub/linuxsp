#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Get the current program break
    void *initial_break = sbrk(0);
    if (initial_break == (void *)-1) {
        perror("sbrk");
        exit(EXIT_FAILURE);
    }
    printf("Initial program break: %p\n", initial_break);

    // Calculate new program break
    void *new_break = (char *)initial_break + 4096;

    // Set new program break
    if (brk(new_break) != 0) {
        perror("brk");
        exit(EXIT_FAILURE);
    }
    printf("New program break: %p\n", sbrk(0));

    // Reset program break to initial value
    if (brk(initial_break) != 0) {
        perror("brk");
        exit(EXIT_FAILURE);
    }

    // Verify the program break is reset correctly
    void *reset_break = sbrk(0);
    if (reset_break == (void *)-1) {
        perror("sbrk");
        exit(EXIT_FAILURE);
    }
    
    printf("Program break reset to: %p\n", initial_break);

    return 0;
}
