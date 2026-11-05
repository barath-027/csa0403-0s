#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    char buf[64];
    int fd = open("patient.txt", O_RDONLY);          /* file management */
    if (fd < 0) { perror("open"); return 1; }
    ssize_t n = read(fd, buf, sizeof buf);           /* the system call under study */
    write(STDOUT_FILENO, buf, (size_t)n);            /* device management (terminal) */
    close(fd);
    return 0;
}
