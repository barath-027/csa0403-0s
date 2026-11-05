#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
/* Compare an ordinary (non-inlined) function call with a real system call (getppid). */
__attribute__((noinline)) long plain_call(long x) { __asm__ volatile("" : "+r"(x)); return x + 1; }
static double now(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return t.tv_sec + t.tv_nsec / 1e9; }
int main(void)
{
    const long N = 5000000; long s = 0;
    double t0 = now();
    for (long i = 0; i < N; i++) s += plain_call(i);
    double tf = now() - t0;
    t0 = now();
    for (long i = 0; i < N; i++) s += syscall(SYS_getppid);
    double ts = now() - t0;
    printf("function call : %.1f ns each\n", tf / N * 1e9);
    printf("system call   : %.1f ns each\n", ts / N * 1e9);
    printf("syscall / call = %.0fx   (checksum %ld)\n", ts / tf, s);
    return 0;
}
