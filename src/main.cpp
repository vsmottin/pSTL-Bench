#ifdef __GNUG__
// we have the case that we use gcc. this means tbb will be used for parallel stl
// potential thread limits have to be configured

#include "tbb_thread_control.h"

#endif

#include <benchmark/benchmark.h>
#include "benchmarks/b1/b1_group.h"
#include "benchmarks/b2/b2_group.h"
#include "benchmarks/b3/b3_group.h"
#include "benchmarks/b4/b4_group.h"
#include "benchmarks/b5/b5_group.h"
#include "benchmarks/b6/b6_group.h"
#include "benchmarks/b7/b7_group.h"
#include "benchmarks/b8/b8_group.h"
#include "benchmarks/b9/b9_group.h"

B1_GROUP_BENCHMARKS
B2_GROUP_BENCHMARKS
B3_GROUP_BENCHMARKS
B4_GROUP_BENCHMARKS
B5_GROUP_BENCHMARKS
B6_GROUP_BENCHMARKS
B7_GROUP_BENCHMARKS
B8_GROUP_BENCHMARKS
B9_GROUP_BENCHMARKS

// Run the benchmark
int main(int argc, char **argv) {

#ifdef __GNUG__
    auto tbbThreadControl = init_tbb_thread_control();
#endif

    char arg0_default[] = "benchmark";
    char *args_default = arg0_default;
    if (!argv) {
        argc = 1;
        argv = &args_default;
    }
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();

#ifdef __GNUG__
    tbbThreadControl.release();
#endif

    return 0;
}
