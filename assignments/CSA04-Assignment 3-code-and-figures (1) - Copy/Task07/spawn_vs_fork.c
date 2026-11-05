#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <time.h>
extern char **environ;
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }
int main(void)
{
    const int N = 1000;
    size_t mb = 64; char *big = malloc(mb << 20);           /* a 64 MB parent, like a database server */
    for (size_t i = 0; i < (mb << 20); i += 4096) big[i] = 1;
    char *argv[] = {"true", NULL};
    double t0 = now();
    for (int i = 0; i < N; i++) {
        pid_t p = fork();
        if (p == 0) { execv("/bin/true", argv); _exit(127); }
        waitpid(p, NULL, 0);
    }
    double tf = now() - t0;
    t0 = now();
    for (int i = 0; i < N; i++) {
        pid_t p;
        posix_spawn(&p, "/bin/true", NULL, NULL, argv, environ);
        waitpid(p, NULL, 0);
    }
    double tp = now() - t0;
    printf("fork+exec  x%d: %.3f s (%.0f us each)\n", N, tf, tf / N * 1e6);
    printf("posix_spawn x%d: %.3f s (%.0f us each)\n", N, tp, tp / N * 1e6);
    free(big);
    return 0;
}
