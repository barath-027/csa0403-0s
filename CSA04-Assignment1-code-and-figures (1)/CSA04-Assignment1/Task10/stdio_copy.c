#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
/* fread/fwrite copy with 1-byte-at-a-time calls: library buffering batches the real system calls */
int main(int argc, char **argv)
{
    if (argc != 3) return 2;
    FILE *in = fopen(argv[1], "rb"), *out = fopen(argv[2], "wb");
    if (!in || !out) { perror("fopen"); return 1; }
    int c; long n = 0;
    while (fread(&c, 1, 1, in) == 1) { fwrite(&c, 1, 1, out); n++; }
    fclose(in); fclose(out);
    printf("library calls: %ld fread + %ld fwrite\n", n, n);
    return 0;
}
