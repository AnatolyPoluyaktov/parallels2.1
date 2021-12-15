## for Ubuntu 20

Инструкция по запуску:

1. mpicc main.c -o main

2. vim my-hostfile
 - localhost slots=4

3. mpirun -np 50 --hostfile my-hostfile main
