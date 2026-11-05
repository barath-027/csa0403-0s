# CSA04 – Operating Systems – Assignment 1 (CO1)

**Name:** _your name_  **Register number:** _your register number_

## Environment used for the results in the report
- Linux distribution: Ubuntu 24.04.5 LTS (x86-64), 2 virtual CPUs
- Compiler: gcc 13.3.0
- Compile command: `gcc -std=c11 -Wall -Wextra -pthread file.c -o file`

## Folders
| Folder | Contents | Result |
|---|---|---|
| Task05 | read_demo.c, strace output | read() path shown with strace: openat, read, write, close |
| Task06 | copy_file.c (Complete the Code), mmap_copy.c, syscall_cost.c | Output matches expected: 10001 / 21 / 4 read() calls; syscall ≈ 76× function call |
| Task07 | shell.c (Complete the Code), shell_variant.c, spawn_vs_fork.c | Output matches expected; variant shows duplicated lines when stdout is redirected |
| Task08 | protection_demo.c | Privileged instruction and bad memory accesses are killed with SIGSEGV |
| Task10 | copy_bench.c, stdio_copy.c, fork_vs_thread.c | read() counts = n/b; fork 41× slower than thread creation |
| figs | diagrams and terminal screenshots | used in the report |

Tasks 1–4, 9, 11 and 12 are written analysis (see the Word report).

## How to run
```
gcc -std=c11 -Wall -Wextra Task06/copy_file.c -o Task06/copy_file && ./Task06/copy_file
strace -c -f -e trace=read,write ./Task06/copy_file > /dev/null
gcc -std=c11 -Wall -Wextra Task07/shell.c -o Task07/shell && ./Task07/shell
gcc -std=c11 -Wall -Wextra Task08/protection_demo.c -o Task08/protection_demo && ./Task08/protection_demo
gcc -std=c11 -Wall -Wextra -pthread Task10/fork_vs_thread.c -o Task10/fork_vs_thread && ./Task10/fork_vs_thread
```
Re-run everything on your own machine and replace the outputs/screenshots with yours before submitting.
