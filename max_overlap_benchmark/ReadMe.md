Benchmarking for multiple algorithms that compute the longest common sequence in a string with no extra space.
One of these will be used in the deflate algorithm to compare the search and lookahead buffers.

Algorithms include simple for loops, but also extensions such as SIMD and AVX.

Results:

1 - Max overlap - 255 for deflate
2 - No overlap - 0
3 - Partial overlap - 130

Running Mismatch.exe
Run on (20 X 2803 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x10)
  L1 Instruction 32 KiB (x10)
  L2 Unified 1280 KiB (x10)
  L3 Unified 24576 KiB (x1)
-----------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations
-----------------------------------------------------------------------
BENCH_for_loop_byte/1             0.944 ns        0.928 ns    640000000
BENCH_for_loop_byte/2              1.10 ns         1.11 ns    746666667
BENCH_for_loop_byte/3              1.18 ns        0.906 ns   1000000000
BENCH_while_loop_byte/1            1.18 ns        0.906 ns   1000000000
BENCH_while_loop_byte/2            1.18 ns        0.439 ns   1600000000
BENCH_while_loop_byte/3           0.946 ns        0.942 ns    746666667
BENCH_while_loop_int/1            0.943 ns        0.942 ns    746666667
BENCH_while_loop_int/2            0.944 ns        0.942 ns    746666667
BENCH_while_loop_int/3            0.944 ns        0.942 ns    746666667
BENCH_while_loop_zlib/1            1.22 ns        0.212 ns   4197730722
BENCH_while_loop_zlib/2            1.24 ns        0.174 ns   11200000000
BENCH_while_loop_zlib/3            1.26 ns        0.146 ns   8960000000
BENCH_while_loop_less_vars/1       1.25 ns        0.474 ns   1120000000
BENCH_while_loop_less_vars/2       1.28 ns        0.578 ns   1947826087
BENCH_while_loop_less_vars/3       1.20 ns        0.785 ns   1792000000
BENCH_mismatch_byte/1              1.27 ns        0.562 ns   1000000000
BENCH_mismatch_byte/2              1.19 ns        0.963 ns    746666667
BENCH_mismatch_byte/3              1.22 ns        0.766 ns   1000000000
BENCH_simd/1                       1.21 ns        0.578 ns   1000000000
BENCH_simd/2                       1.18 ns         1.02 ns   1000000000
BENCH_simd/3                       1.21 ns         1.12 ns    640000000
BENCH_avx/1                        1.17 ns        0.977 ns    896000000
BENCH_avx/2                        1.19 ns        0.952 ns    640000000
BENCH_avx/3                        1.17 ns         1.03 ns    640000000
BENCH_multiple_ifs/1               1.17 ns        0.984 ns   1000000000
BENCH_multiple_ifs/2               1.18 ns        0.991 ns   1120000000
BENCH_multiple_ifs/3               1.16 ns         1.06 ns    560000000
BENCH_memcmp_inc/1                 1.18 ns         1.10 ns    640000000
BENCH_memcmp_inc/2                 1.36 ns         1.25 ns    640000000
BENCH_memcmp_inc/3                 1.17 ns         1.10 ns    640000000
BENCH_memcmp_inc_opt/1             1.17 ns         1.17 ns    746666667
BENCH_memcmp_inc_opt/2             1.17 ns         1.12 ns    896000000
BENCH_memcmp_inc_opt/3             1.17 ns         1.07 ns    640000000
BENCH_memcmp_dec/1                 1.18 ns        0.969 ns   1000000000
BENCH_memcmp_dec/2                 1.21 ns        0.562 ns   1000000000
BENCH_memcmp_dec/3                 1.14 ns         1.13 ns    896000000