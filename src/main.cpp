#include <benchmark/benchmark.h>
#include "benchmarks/b1/b1_group.h"
#include "benchmarks/b2/b2_group.h"
#include "benchmarks/b3/b3_group.h"

B1_GROUP_BENCHMARKS
B2_GROUP_BENCHMARKS
B3_GROUP_BENCHMARKS

// Run the benchmark
BENCHMARK_MAIN();