#!/usr/bin/env bash
# vgclean — close all non‑stdio fds before starting

for fd in /proc/$$/fd/*; do
  num=${fd##*/}; (( num > 2 )) && eval "exec $num>&-"
done
exec valgrind --leak-check=full --track-origins=yes --track-fds=all --trace-children=yes --suppressions=readline.sup "$@"