#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];

    // Open the file for reading
    fd = open("input.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    // Read from the file
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Write the buffer to standard output
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing to stdout");
            close(fd);
            return 1;
        }
    }

    if (bytesRead == -1) {
        perror("Error reading the file");
    }

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing the file");
        return 1;
    }

    return 0;
}
