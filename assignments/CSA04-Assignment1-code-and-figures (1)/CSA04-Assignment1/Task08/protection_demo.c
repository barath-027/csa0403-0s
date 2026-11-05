#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
/* Each test runs in its own child so the hardware/OS reaction can be observed by the parent. */
static void report(const char *what, pid_t p)
{
    int st; waitpid(p, &st, 0);
    if (WIFSIGNALED(st)) printf("%-48s -> killed by signal %d (%s)\n", what, WTERMSIG(st), strsignal(WTERMSIG(st)));
    else printf("%-48s -> exited normally (%d)\n", what, WEXITSTATUS(st));
}
int main(void)
{
    pid_t p;
    fflush(stdout);
    if ((p = fork()) == 0) {
#if defined(__x86_64__) || defined(__i386__)
        __asm__ volatile("cli");               /* privileged instruction: disable interrupts */
#elif defined(__aarch64__)
        __asm__ volatile("msr daifset, #2");   /* privileged on ARM64: mask IRQ */
#endif
        _exit(0);
    }
    report("user mode runs privileged instruction (cli)", p);
    if ((p = fork()) == 0) { volatile int *bad = (int *)8; *bad = 1; _exit(0); }
    report("write to an unmapped address (0x8)", p);
    if ((p = fork()) == 0) { char *s = "text"; ((volatile char *)s)[0] = 'X'; _exit(0); }
    report("write into read-only memory (string literal)", p);
    if ((p = fork()) == 0) { char a[4]; (void)a; volatile char *q = (char *)0x7fff00000000ULL; (void)*q; _exit(0); }
    report("read another process's address range (guess)", p);
    return 0;
}
