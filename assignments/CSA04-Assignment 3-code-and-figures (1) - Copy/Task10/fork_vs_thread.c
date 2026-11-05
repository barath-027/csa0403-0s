#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>

#define COUNT 1000
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }
static void *worker(void *arg) { (void)arg; return NULL; }

int main(void)
{
    /* give the process a realistic heap so fork() has page tables to copy: 64 MB touched */
    size_t mb = 64; char *big = malloc(mb << 20);
    for (size_t i = 0; i < (mb << 20); i += 4096) big[i] = 1;

    double t0 = now();
    for (int i = 0; i < COUNT; i++) {
        pid_t p = fork();
        if (p == 0) _exit(0);
        waitpid(p, NULL, 0);
    }
    double tf = now() - t0;

    t0 = now();
    for (int i = 0; i < COUNT; i++) {
        pthread_t t;
        pthread_create(&t, NULL, worker, NULL);
        pthread_join(t, NULL);
    }
    double tt = now() - t0;
    printf("%d processes (fork+wait): %.4f s  (%.1f us each)\n", COUNT, tf, tf / COUNT * 1e6);
    printf("%d threads (create+join): %.4f s  (%.1f us each)\n", COUNT, tt, tt / COUNT * 1e6);
    printf("ratio process/thread = %.1fx\n", tf / tt);
    free(big);
    return 0;
}
