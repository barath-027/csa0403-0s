#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* Usage: copy_bench src dst bufsize  -- copies with read()/write(), prints read() count and time */
int main(int argc, char **argv)
{
    if (argc != 4) { fprintf(stderr, "usage: %s src dst bufsize\n", argv[0]); return 2; }
    size_t bs = (size_t)atol(argv[3]);
    char *buf = malloc(bs);
    int in = open(argv[1], O_RDONLY), out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (in < 0 || out < 0 || !buf) { perror("open/malloc"); return 1; }
    struct timespec a, b; clock_gettime(CLOCK_MONOTONIC, &a);
    long reads = 0; ssize_t n;
    while ((n = read(in, buf, bs)) > 0) { reads++; if (write(out, buf, (size_t)n) != n) { perror("write"); return 1; } }
    clock_gettime(CLOCK_MONOTONIC, &b);
    close(in); close(out); free(buf);
    printf("bufsize %8zu  read() calls %9ld  wall %.4f s\n", bs, reads,
           (b.tv_sec - a.tv_sec) + (b.tv_nsec - a.tv_nsec) / 1e9);
    return 0;
}
