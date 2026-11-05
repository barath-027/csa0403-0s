OS PRACTICALS - CSA04 OPERATING SYSTEMS LAB  (40 C++ programs)
================================================================

Requirements : Linux / Ubuntu / WSL / macOS with g++ installed
               (programs use fork, pthreads, semaphores, UNIX system calls)

HOW TO RUN A SINGLE PROGRAM
---------------------------
   g++ 01_Process_Creation_fork_getpid.cpp -o prog -pthread
   ./prog

HOW TO RUN BY NUMBER (easiest)
------------------------------
   chmod +x run.sh
   ./run.sh 5        -> compiles and runs program 05
   ./run.sh 12       -> compiles and runs program 12

LIST OF PROGRAMS
----------------
 1  Process creation (fork, getpid, getppid)
 2  File copy using system calls
 3  FCFS scheduling
 4  Shortest-execution-time-first selection
 5  Priority scheduling (highest priority first)
 6  Preemptive priority scheduling
 7  Non-preemptive SJF
 8  Round Robin scheduling
 9  IPC - shared memory
10  IPC - message queue
11  Multithreading
12  Dining Philosophers
13  Memory allocation strategies (First/Best/Worst fit)
14  Single level directory
15  Two level directory
16  Random access file (employee details)
17  Banker's algorithm
18  Producer-Consumer (semaphores)
19  Mutex locks synchronization
20  Reader-Writer (semaphores)
21  Worst fit
22  Best fit
23  First fit
24  UNIX system calls for file management
25  I/O system calls (fcntl, lseek, stat, opendir, readdir)
26  File management operations
27  ls command simulation      (try: ./prog -l)
28  grep command simulation    (try: ./prog -n -i pattern file)
29  Classical synchronization problem (Sleeping Barber)
30  Threads: create, join, equal, exit
31  FIFO page replacement
32  LRU page replacement
33  Optimal page replacement
34  Sequential file allocation
35  Indexed file allocation
36  Linked file allocation
37  FCFS disk scheduling
38  SCAN disk scheduling
39  C-SCAN disk scheduling
40  Linux file permissions and user types
