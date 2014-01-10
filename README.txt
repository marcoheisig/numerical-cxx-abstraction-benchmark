           __________________________________________________

                THE COST OF C++ ABSTRACTIONS ON VARIOUS
                               COMPILERS
           __________________________________________________


                            <2014-01-03 Fr>

This benchmark measures the cost of various C++ abstractions for a
typical numerical workload - a Jacobi solver. It is roughly inspired by
the [Stepanov Benchmark].

The Makefile can be easily extended for any number of different
compilers. Adding new benchmarks is also straightforward. All generated
benchmarks can be invoked seperately or via the generated run.sh script.

Feedback (marco.heisig@fau.de) is welcome - have fun.


[Stepanov Benchmark] http:www.open-std.org/jtc1/sc22/wg21/docs/D_3.cpp
