#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mpi.h"



int main(int argc, char** argv) {
    int SIZE  = 1000;
    int arr[SIZE];
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand() % 1000;
    }
    int num_proc, curr_proc;
    clock_t begin;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &curr_proc);
    int  size, r;
    size = SIZE / num_proc;
    r = SIZE % num_proc;
    int left,right;

    if (curr_proc >= r){
        left = size * curr_proc + r;
        right = (size * curr_proc + r + size) - 1;
    }

    else{
        left = (size + 1) * curr_proc;
        right = (size + 1) * (curr_proc + 1) - 1;
    };

    if (curr_proc == 0)
        begin = clock();
    int result[2] = {arr[left], arr[left]};
    for (int i = left; i <= right; ++i) {
        if (arr[i] < result[0])
            result[0] = arr[i];
        if (arr[i] > result[1])
            result[1] = arr[i];
    }

    if (num_proc != 1) {
        if (curr_proc != 0) {
            MPI_Send(&result, 2, MPI_INT, 0, 11, MPI_COMM_WORLD);
            MPI_Finalize();
            return 0;
        } else {
            int local[2];
            for (int i = 1; i < num_proc; ++i) {
                MPI_Recv(&local, 2, MPI_INT, i, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (local[0] < result[0])
                    result[0] = local[0];
                if (local[1] > result[1])
                    result[1] = local[1];
            }
        }
    }
    printf("Min = %d, Max = %d.\n", result[0], result[1]);
    clock_t end = clock();
    printf("Time = %f", (double)(end - begin) / CLOCKS_PER_SEC);
    MPI_Finalize();
    return 0;
}
