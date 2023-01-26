#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Insufficient parameters passed.\n");
        exit(1);
    }

    int input = open(argv[1], O_RDONLY);
    if(input < 0)
    {
        printf("Error opening input file.\n");
        exit(1);
    }

    int output = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
    if(output < 0)
    {
        printf("Error creating and opening output file.\n");
        exit(1);
    }

    char buffer[1024];
    size_t bytes_read;
    while((bytes_read = read(input, buffer, sizeof(buffer))) > 0)
    {
        size_t bytes_written = write(output, buffer, bytes_read);
        if(bytes_written < 0)
        {
            printf("Error writing to output file.\n");
            exit(1);
        }
    }

    close(input);
    close(output);

    printf("The contents of file %s have been successfully copied into the %s file.\n", argv[1], argv[2]);
    return 0;
}
