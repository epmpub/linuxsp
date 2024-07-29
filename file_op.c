#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("Starting program\n");
    FILE *file_ptr;
    file_ptr = fopen("file_op.txt","w");

    if (file_ptr == NULL)
    {
        printf("Error for open file\n");
        exit(1);
    }

    fprintf(file_ptr,"Hello world content!\n");
    fclose(file_ptr);

    printf("Done\n");
    
    return 0;
}
