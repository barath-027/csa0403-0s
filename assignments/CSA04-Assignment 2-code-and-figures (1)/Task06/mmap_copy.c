#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
/* Alternative concept: copy a file through memory-mapped files (a handful of system calls). */
int main(int argc, char **argv)
{
    if (argc != 3) return 2;
    int in = open(argv[1], O_RDONLY); struct stat st; fstat(in, &st);
    int out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (ftruncate(out, st.st_size) < 0) { perror("ftruncate"); return 1; }
    char *s = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, in, 0);
    char *d = mmap(NULL, (size_t)st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, out, 0);
    if (s == MAP_FAILED || d == MAP_FAILED) { perror("mmap"); return 1; }
    memcpy(d, s, (size_t)st.st_size);          /* page faults, not system calls, move the data */
    msync(d, (size_t)st.st_size, MS_SYNC);
    munmap(s, (size_t)st.st_size); munmap(d, (size_t)st.st_size);
    close(in); close(out);
    return 0;
}
