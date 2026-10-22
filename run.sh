#!/bin/bash
# Usage: ./run.sh <program number>   e.g.  ./run.sh 7
if [ -z "$1" ]; then echo "Usage: ./run.sh <program number 1-40>"; exit 1; fi
n=$(printf "%02d" $((10#$1)))
f=$(ls ${n}_*.cpp 2>/dev/null | head -1)
if [ -z "$f" ]; then echo "Program $n not found"; exit 1; fi
echo ">>> Compiling $f"
g++ -std=c++17 "$f" -o /tmp/os_prog_$n -pthread || exit 1
echo ">>> Running"; echo
shift
/tmp/os_prog_$n "$@"
