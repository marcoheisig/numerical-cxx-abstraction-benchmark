/* Numerical C++ Abstraction Benchmark - main file */

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sys/time.h>
#include "config.hh"

int main(int argc, char** argv) {
    if(1 == argc) {
        printf("Usage: %s iterations\n", argv[0]);
        exit(EXIT_FAILURE);
    };
    size_t iterations = atoi(argv[1]);

    std::vector<real>  src(cells, 42.0);
    std::vector<real> dest(cells, 42.0);

    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    for(size_t i  = 0; i  < iterations/2;  ++i ) {
        run(src, dest);
        run(dest, src);
    }
    struct timeval end_time;
    gettimeofday(&end_time, NULL);

    long sec  = end_time.tv_sec  - start_time.tv_sec;
    long usec = end_time.tv_usec - start_time.tv_usec;
    double seconds     = (double)sec + (double)usec / (1000.0 * 1000.0);

    gettimeofday(&start_time, NULL);
    for(size_t i  = 0; i  < iterations/2;  ++i ) {
        runb(src, dest);
        runb(dest, src);
    }
    gettimeofday(&end_time, NULL);

    sec  = end_time.tv_sec  - start_time.tv_sec;
    usec = end_time.tv_usec - start_time.tv_usec;
    double oseconds     = (double)sec + (double)usec / (1000.0 * 1000.0);

	seconds -= oseconds;

    size_t flop_total  = (size_t)iterations * flops_per_iter;
    size_t flops       = (size_t)((double)flop_total / seconds);
    double gigaflops   = (double)flops      / (1000.0 * 1000.0 * 1000.0);
    double miterations = (double)iterations / (1000.0 * 1000.0);
    printf("%-20s %5.2f Gflops, %5.2fM iterations, %5.2f seconds, domain: %lux%lu\n",
           argv[0],gigaflops,        miterations,        seconds,        rows, columns);
    return 0;
}


