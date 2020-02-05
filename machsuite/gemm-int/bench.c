#include "gemm.h"

void run_benchmark() {
    struct bench_args_t args;
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            args.m1[i * row_size + j] = 1 + i * row_size + j;
            args.m2[i * row_size + j] = rand() / (N);
            args.prod[i * row_size + j] = 0;
        }
    }
    gemm( args.m1, args.m2, args.prod );
    printf("One example output is %d \n", args.prod[N-1]);
}

int main () {
    run_benchmark();
    return 1;
}
